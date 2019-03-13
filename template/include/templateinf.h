

#ifndef __MLT_TEMPLATE_INTERFACE_H__
#define __MLT_TEMPLATE_INTERFACE_H__

#include <vector>
#include <deque>
#include <string>

using namespace std;

typedef struct
{
	vector<string>  system_template_types; //系统模板分类，保存模板时，根据此信息会自动在模板用户存储路径建立相应目录，并把模板拷贝到此目录
	string user_template_path; //模板用户存储路径
	string user_temp_path; //临时模板解压，存储路径， 用于
}MM_TEMPLATE_CONFIG;

typedef struct 
{
	int track_index;
	int producer_index;

}MM_PRODUCER_INDEX;


typedef void * MM_PRODUCER_HANDLE;// 接口使用
/*
程序实现可以如下定义，根据需要添加
typedef struct
{
	MM_PRODUCER_INDEX producer_index;
	Mlt::producer producer;
}MM_PRODUCER_HANDLE;
*/

typedef struct
{
	MM_PRODUCER_INDEX producer_index;
	int filter_index;
	int parameter_index;
}MM_FILTER_PARAMETER_INDEX;

class QVariant; //暂时使用QVariant 长久使用自己写的统一变量对象，不依赖QT
#define UniVariant QVariant


typedef struct 
{
	string para_name;
	string para_unit; //单位
	int value_invalid_mask;  //  低1，2，3位分别使能下面的缺省值，最大值，最小值，如 3 （0011）表示有缺省值和最大值，无最小值
	UniVariant default_value;
	UniVariant max_value;
	UniVariant min_value;

}MM_PARAMETER_INFO;


typedef void * MM_MLT_HANDLE;//接口定义

/*
程序实现可以如下定义，根据需要添加
typedef struct 
{
	string file_name;
	string file_thumb;
//	string folder_decompress;

	MM_PRODUCER_HANDLE producer;// 整个模板的PRODUCER

}MM_MLT_INFO;
*/


int tp_init_template_module(const MM_TEMPLATE_CONFIG *pConfig);//初始化，传递配置信息

int tp_exit_template_module();//退出模块

MM_MLT_HANDLE mm_open_mlt_file(const char *mlt_file_name);//打开模板和工程文件都可以

int mm_close_mlt_file(MM_MLT_HANDLE mlt_info);

int mm_get_track_count(MM_MLT_HANDLE  mlt_info);//此文件有多少轨道

int mm_get_producer_count(MM_MLT_HANDLE  mlt_info, int track_index);//轨道上有多少个PRODUCER

MM_PRODUCER_HANDLE mm_open_producer(MM_MLT_HANDLE  mlt_info, int track_index, int producer_index);

int mm_close_producer(MM_PRODUCER_HANDLE producer);

int mm_get_filters_count(MM_PRODUCER_HANDLE producer);

int mm_get_parameters_count(MM_PRODUCER_HANDLE producer, int filter_index);

int mm_get_parameter_info(MM_PRODUCER_HANDLE producer, int filter_index, int parameter_index, MM_PARAMETER_INFO &parameter_info);

int mm_set_speed(MM_MLT_HANDLE  mlt_info, double speed); //设置速率变快，变慢

int mm_is_template_file(MM_MLT_HANDLE  mlt_info);//是否为模板文件

void * mm_get_mlt_producer(MM_PRODUCER_HANDLE producer);//返回 Mlt::producer 为避免引用头文件，直接写成void *

int mm_get_resource_info(MM_PRODUCER_HANDLE producer, string out_file_name,
							int64_t *p_out_frame_in, int64_t *p_out_frame_out);//获取资源信息

//获取允许替换的资源文件对应的PRODUCER
int tp_get_can_replace_resource(MM_MLT_HANDLE  mlt_info,  deque<MM_PRODUCER_INDEX> &out_can_replace_resource);

//获取允许设置参数的集合
int tp_get_can_set_filters_parameter(MM_MLT_HANDLE  mlt_info,  deque<MM_FILTER_PARAMETER_INDEX> &out_can_set_parameters);

//替换资源 
int tp_replace_resource(MM_MLT_HANDLE  mlt_info, int track_index, int producer_index, const char *file_name,
							int64_t frame_in, int64_t frame_out);

//设置属性
int tp_set_filter_parameter(MM_PRODUCER_HANDLE, int filter_index, int para_index, UniVariant &value);

//模板分两种：
//单PRODUCER xml 模板  不ZIP压缩
//工程PRODUCER  ZIP压缩 并打包用户资源（ 没有在can_replace_resource 的资源列表里，又不是系统路径的资源）。
//底层插件专门实现处理以上两种类型模板的PRODUCER

//以下信息，添加新的属性，记录到对应的PRODUCER 和FILTER
//deque<MM_PRODUCER_INDEX> &can_replace_resource, //设置哪些资源允许替换
//deque<MM_FILTER_PARAMETER_INDEX> &can_set_parameters, //设置哪些参数允许在模板里设置

//保存工程成为模板  替换的资源自动添加一 POSITION/RESIZE 滤镜，使得资源和分辨率无关。
//
int tp_save_to_template(MM_MLT_HANDLE  mlt_info, 
						const string &save_template_file,
						const string &template_thumb_file,
						const deque<MM_PRODUCER_INDEX> &can_replace_resource, //设置哪些资源允许替换
						const deque<MM_FILTER_PARAMETER_INDEX> &can_set_parameters, //设置哪些参数允许在模板里设置
						const string &template_type, //对应MM_TEMPLATE_CONFIG里面的system_template_types
						 int meida_type //模板偏向应用于视频， 图片，音频或者文本 作为工程属性记录到XML
						  );

#endif // __MLT_TEMPLATE_INTERFACE_H__
