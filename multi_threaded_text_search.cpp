#include<stdlib.h>
#include<pthread.h>
#include<assert.h>

#include<algorithm>
#include<memory>
#include<fstream>
#include<vector>
#include<iostream>
using namespace std;

//Enable or disable debug logs.
//#define //log cout

const int BUFSIZE = 16*65536;
std::unique_ptr<char> buffer(new char[BUFSIZE]);



class text_search
{
	private:
		unique_ptr<char> buffer;
		vector<pthread_t> threads;
		const unsigned int thread_count;
		const string filename, key;
		ifstream ifs;
		pthread_mutex_t file_read_lock;
		vector< vector<unsigned long long int> >search_index;
		unsigned long long int byte_read;

		int read_file_chunk(vector<string>& buf,const int len, unsigned long long int&start_offset);
		void merge_serach_results_from_threads();

	public:
		text_search(string _filename, string _key, int _thread_count);
		void run_search();
		int read_file_chunk_safe(vector<string>& buf,const int len, unsigned long long int&start_offset);
		void update_search_index(vector<string>& buf, unsigned long long int start_offset, int thread_index);
};

struct thread_data
{
	text_search* obj;
	unsigned int thread_index;
	thread_data(text_search* _obj,  unsigned int _thread_index)
	{
		obj = _obj;
		thread_index = _thread_index;
	}
};

void* dummy_func(void* _arg) 
{
	thread_data* arg = (thread_data*)_arg;
	const int lines_to_read = 5000;
	bool read_file = true;
	while(read_file)
	{
		// 1:- Read a file chunk and set the start_offset.
		vector<string> read_buf;
		unsigned long long int start_offset=0;
		int lines_read = arg->obj->read_file_chunk_safe(read_buf, lines_to_read, start_offset);
		if(lines_read < lines_to_read) // Reached the end;
			read_file = false;

		//log << "start_offset= " << start_offset << endl;
		//2:- Run the string search and fill the vector.
		arg->obj->update_search_index(read_buf, start_offset, arg->thread_index);
	}	

}

text_search::text_search(string _filename, string _key, int _thread_count):
filename( _filename), key(_key), thread_count( _thread_count), file_read_lock(PTHREAD_MUTEX_INITIALIZER)
{
	ifs.rdbuf()->pubsetbuf(buffer.get(), BUFSIZE);

	search_index.resize(_thread_count);
	threads.resize(thread_count);
	byte_read = 0;
	//log<<"Filename = " << filename <<", search-key= " << key << ", thread-count= " <<thread_count <<endl;
}


void text_search::run_search()
{
	ifs.open (filename.c_str(), std::ifstream::in);
	{
		if(ifs.is_open() == false)
		{
			cout<<"\n Unable to open the file\n";
			return;
		}
	}
	thread_data* tmp_ptr[thread_count];

	for(unsigned int i=0; i<thread_count; i++)
	{
		tmp_ptr[i] = new thread_data(this,i); // Skipping delete as it runs till lifetime of process.
		int ret = pthread_create(&threads[i], NULL, dummy_func, tmp_ptr[i]);
		if(ret != 0)
		{
			cout<<"\n Unable to create thread\n";
			assert(false);
		}
	}

	for (unsigned int i = 0; i < thread_count; i++)
	       pthread_join(threads[i], NULL);

	merge_serach_results_from_threads();
	ifs.close();
	for(int i=0; i<thread_count; i++)
		delete tmp_ptr[i];
		
}


int text_search::read_file_chunk_safe(vector<string>& buf,const int len, unsigned long long int&start_offset)
{
	int ret_val = 0;

	pthread_mutex_lock(&file_read_lock);
		ret_val = read_file_chunk(buf, len, start_offset);
	pthread_mutex_unlock(&file_read_lock);

	return ret_val;
}

int text_search::read_file_chunk(vector<string>& buf,const int len, unsigned long long int&start_offset)
{
	start_offset = byte_read;	
	for(int i=0; i<len; i++)
	{
		string buf_str;
		bool err = getline(ifs,buf_str);
		if(err == false)
			return i;
		else
		{	
			buf.push_back(buf_str);
			byte_read +=buf_str.size()+1; // +1 for new-line char.
		}	
	}
	return len;
}

void text_search::update_search_index(vector<string>& buf, unsigned long long int cur_offset, int thread_index)
{
	for(int i=0; i<buf.size(); i++)
	{
		//log << "Scanning line= " << buf[i] << ", offset= " << cur_offset << endl;
		int count = 0;
		size_t nPos = buf[i].find(key, 0); // fist occurrence
		if(nPos == string::npos)
		{
			cur_offset += (1+buf[i].size()); // buf has data of one line. +1 for new line char.
			continue;
		}	

		search_index[thread_index].push_back(cur_offset+nPos); // +1 to offset index 0.
		//log<<" Found at index " << nPos << ", str= " << buf[i] << endl;
		while(nPos != string::npos)
		{
			nPos = buf[i].find(key, nPos+1);
			if(nPos == string::npos)
				break;
			search_index[thread_index].push_back(cur_offset+nPos);// +1 to offset index 0.
			//log<<" Found at index " << nPos  << ", str= " << buf[i] << endl;
		}
		cur_offset += (1+buf[i].size()); // buf has data of one line. +1 for new line char.
		//log <<"cur_offset = " << cur_offset << endl;
	}
}

void text_search::merge_serach_results_from_threads()
{
	vector<unsigned long long int> search_offsets;
	for(unsigned int i=0; i<search_index.size(); i++)
	{
		//log<<"\n Thread " << i+1 <<" found " << search_index[i].size() << endl;  
		for(unsigned int j=0; j<search_index[i].size(); j++)
		{
			search_offsets.push_back(search_index[i][j]);
		}
	}

	// It can use k-way merge instead of sort as entries are already sorted within a thread.
	sort(search_offsets.begin(), search_offsets.end());

	//log<<"\n No of search entries = " << search_offsets.size() <<", printing the entries\n";
	ofstream ofs("my_output.txt");
	for(unsigned int i=0; i<search_offsets.size(); i++)
	{
		cout<< search_offsets[i] << endl;
		//ofs << search_offsets[i] <<":" << key << endl;
	}
	//log<<endl;
	ofs.close();
}



int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		cout<<"\n***** Wrong usage ****";
		cout<<"\n Usage: exe filename searchKey threadCount\n";
		return 0;
	}
	
	int thread_count=atoi(argv[3]);
	if(thread_count == 0)
	{
		cout<<"\n Invalid value for threadCount\n";
		return 0;
	}

	string filename(argv[1]);
	string search_key(argv[2]);

	text_search obj_search_app(filename, search_key, thread_count);
	obj_search_app.run_search();

	return 0;
}
