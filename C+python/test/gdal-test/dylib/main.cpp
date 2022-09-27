

#include <iostream>
#include <streambuf>
#include <fstream>
#include <cstdio>
#include <gdal.h>
#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()
#include <opencv2/opencv.hpp>

#include <string>
#include <algorithm>

#define BYTE short
extern "C"
void print_line() {
	std::cout << "\n----------------------\n" << std::endl;
}

extern "C"
char* read_txt( char *path ) {
    printf( "path: %s\n", path );
    char res[ 255 ];

    FILE *fpr = fopen( path, "r" );
    fgets( res, 255, ( FILE* )fpr );
    printf( "res: %s\n", res );
    return res;
}

extern "C"
void test( int x ) {
    printf( "%d\n", x ^ 3 );
}

std::string getBytesAsHexString( uint8_t * data, size_t size ) {
	std::stringstream stream;
	stream << std::hex << std::uppercase << std::setfill('0');
	for (size_t i = 0; i < size; ++i) {
		stream << std::setw(2) << static_cast< uint32_t >( data[i] & 0xff ) << " ";
	}
	return stream.str();
}
extern "C"
int main()
{
    // std::string filename( "/Users/xsl/SVDNB_npp_20220501-20220531_75N060E_vcmslcfg_v10_c202206071200.avg_rade9h.tif" );
    // std::string filename( "/Users/xsl/SVDNB_npp_20220501-20220531_75N060E_vcmslcfg_v10_c202206071200.cf_cvg.tif" );
    std::string filename( "/Users/xsl/SVDNB_npp_20220501-20220531_75N060E_vcmslcfg_v10_c202206071200.cvg.tif" );
    GDALDataset *p_dataset;
    GDALAllRegister();
    p_dataset = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly );
    if( p_dataset == NULL )
    {
        std::cout << "open ttf file failed" << std::endl;
		GDALDestroyDriverManager();
		exit(1);

    }
    int x_size = p_dataset->GetRasterXSize();
    int y_size = p_dataset->GetRasterYSize();
    int band_count = p_dataset->GetRasterCount();
    std::string description = p_dataset->GetDescription();
    double tif_info[ 6 ];
    CPLErr result_transfrom = p_dataset->GetGeoTransform( tif_info );
    std::cout << "des: " << description << std::endl;
    printf( "x_size: %d\n", x_size );
    printf( "y_size: %d\n", y_size );
    printf( "band_count: %d\n", band_count );
    std::cout << "坐标变换系数:";
	std::for_each( tif_info, tif_info + 6, []( double x ){ printf( "%.15lf ", x ); } );
    print_line();

    GDALRasterBand *p_band = p_dataset->GetRasterBand( 1 );		// 获取对应波段
		
    // 读取图像高程数据 
    int num_iamge_size = 0;		//数据计数
    BYTE *pafScanline = new BYTE[ x_size * y_size ];
    p_band->RasterIO( GF_Read, 0, 0, x_size, y_size, pafScanline, x_size, y_size, GDALDataType( p_band->GetRasterDataType() ), 0, 0);
    for ( int i = 0; i < x_size; i++ ) {
        for ( int j = 0; j < y_size; j++ ) {
            num_iamge_size++;
            //if (i<10 && j < 10)
            std::cout << pafScanline[ i * y_size + j ] << std::endl;
        }
        //cout << i << "---" << pafScanline[i*nImgSizeY] << endl;
    }
    std::cout << "total:" << num_iamge_size << std::endl;

    delete[] pafScanline;
    
    GDALRasterBand* band = p_dataset->GetRasterBand( 1 );
    int x_band_size = 0;
	int y_band_size = 0;
    GByte *tif_data = static_cast< GByte * >( CPLMalloc( x_size * y_size ) );
	band->GetBlockSize( &x_size, &y_size );
    band->ReadBlock( 5000, 3000, tif_data );
    // std::cout << "one block data: " << getBytesAsHexString( tif_data, x_size * y_size ) << std::endl;
    // p_dataset->GetOpenDatasets(  );
    int i = 0;
    int j = 0;
    double Xp = tif_info[0] + j * tif_info[1];
    double Yp = tif_info[3] + i * tif_info[5];

    delete p_dataset;



    cv::Mat image;
    image = cv::imread( filename, 0 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    uchar *image_data = image.data;
    i = 0;
    j = 0;
    image_data = image.data + i * image.step + j * image.elemSize();
    printf( "%d\n", *image_data );
    // cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
    // imshow( "Display Image", image );
    // cv::waitKey(0);




    //输出tfw文件
	//cout << "准备输出tfw文件：" << endl;
	//double gt[6];
	//GDALGetGeoTransform(poDataset, gt);
	//for (auto value : gt)
	//	cout << "gt:" << (int)value << " ";
	//cout << endl;
	//fstream tfw;
	//string tmpname = file_path_name;
	//tmpname = tmpname.substr(0, tmpname.find_last_of('.') + 1) + "tfw";
	//tfw.open(tmpname, ios::out);
	//tfw << fixed;
	//tfw << setprecision(5);
	//tfw << gt[1] << endl;
	//tfw << gt[2] << endl;
	//tfw << gt[4] << endl;
	//tfw << gt[5] << endl;
	//tfw << gt[0] << endl;
	//tfw << gt[3] << endl;
	//tfw.close();
}

