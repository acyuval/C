#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>
#include <vector>

#pragma pack(push, 2)                    // The elements must start on 16-bit intervals

struct bitmap_file_header {
    char header[2] { 'B', 'M' };
    int32_t file_size;
    int32_t reserved { 0 };
    int32_t data_offset;
};

#pragma pack(pop)                         

struct bitmap_info_header {
    int32_t header_size{40};
    int32_t width;
    int32_t height;
    int16_t planes{1};
    int16_t bits_per_pixel{24};
    int32_t compression{0};
    int32_t data_size{0};
    int32_t horizontal_resolution{2400};
    int32_t vertical_resolution{2400};
    int32_t colours{0};
    int32_t important_colours{0};
};

struct pixel {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
};

class bitmap {
private:
	int width{800};
	int height{600};
	std::string filename;                           
	std::vector<pixel> pixels;                     

public:
	// Constructor
	bitmap(std::string filename) : filename(filename), pixels(width*height) {}
	void set_pixel(int x, int y, pixel p);         
	void set_row(int rownum, pixel p);             
	void set_all(pixel p);                         
	void set_col(int row, pixel p) ;
    bool write();                                
    void CrissCross(pixel p) ;
};

#endif /* BITMAP_H_ */
