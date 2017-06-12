#include<stdio.h>
#include<stdlib.h>
#include<err.h>
#include<stdint.h>
#include<fcntl.h>
#include<unistd.h>

void readChar(int source, char* input, uint8_t count)
{
  if(read(source, input, count) != count)
  {
    close(source);
    errx(13, "Sum Ting Wong with header");
  }
}


void read16(int source, uint16_t* input)
{
  if(read(source, input, 2) != 2)
  {
    close(source);
    errx(13, "Sum Ting Wong in header");
  }
}


void readu32(int source, uint32_t* input)
{
  if(read(source, input, 4) != 4)
  {
    close(source);
    errx(13, "Sum Ting Wong in header");
  }
}

void read32(int source, int32_t* input)
{
  if(read(source, input, 4) != 4)
  {
    close(source);
    errx(13, "Sum Ting Wong in header");
  }
}

void writeChar(int source, int output, char* array, uint32_t size)
{
  if (!write(output, array, size))
  {
    close(output);
    close(source);
    errx(15, "Writing error");
  }
}

void write16(int source, int output, uint16_t* number)
{
  if (!write(output, number, 2))
  {
    close(output);
    close(source);
    errx(15, "Writing error");
  }
}

void write32(int source, int output, int32_t* array)
{
  if (!write(output, array, 4))
  {
    close(output);
    close(source);
    errx(15, "Writing error");
  }
}

void writeu32(int source, int output, uint32_t* array)
{
  if (!write(output, array, 4))
  {
    close(output);
    close(source);
    errx(15, "Writing error");
  }
}

void drawingFunction(unsigned char buffer[1650][1650][3], int32_t height, int32_t  width, uint8_t offset)
{
  for(int32_t i = 0; i < height; i++)
  {
    for(int32_t j = 0; j < width; j++)
    {
      if ((i == (offset - 1) && j == (offset - 1) ) || 
      (i == (offset - 1) && j == (width - offset) ) ||
      (i == height - offset && j == (offset - 1) ) || 
      (i == height - offset && j  == width - offset))
      {
        buffer[i][j][0] = 0;
        buffer[i][j][1] = 0; //black
        buffer[i][j][2] = 0;
        continue;
      }
      if(i == (offset - 1) && j >= (offset - 1) && j <= width - offset)
      {
        buffer[i][j][0] = 0;
        buffer[i][j][1] = 0;
        buffer[i][j][2] = 255; // red
      }
      if( (i == (height - offset )) && j >= (offset - 1) && 
      (j <= width - offset) )
      {
        buffer[i][j][0] = 0;
        buffer[i][j][1] = 255; // green
        buffer[i][j][2] = 0;
      }
      if( (j == (offset - 1) || j == width - offset) && 
      (i > (offset - 1) && (i < height - offset) ) )
      {
        buffer[i][j][0] = 255; // blue
        buffer[i][j][1] = 0;
        buffer[i][j][2] = 0;
      }
    }
  }
}

void bonusDrawing(unsigned char image[1650][1650][3], int32_t height, int32_t width, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
  for(int32_t i = (height / 4); i <= 3 * (height / 4); i++)
  {
    image[i - 1][width/2][0] = BLUE;
    image[i - 1][width/2][1] = GREEN;
    image[i - 1][width/2][2] = RED;
  }
  for(int32_t i = (width / 4); i <= 3 * (width / 4); i++)
  {
    image[height / 2][i - 1][0] = BLUE;
    image[height / 2][i - 1][1] = GREEN;
    image[height / 2][i - 1][2] = RED;
  }
}

int main (int argc, char* argv[])
{
  if(argc != 3)
  {
    errx(11, "Give exactly two file names pls thx");
  }
  
  int source;

  if( (source = open(argv[1], O_RDONLY) ) == -1)
  {
    errx(12, "I don't seem to be able to open or read from that :<");
  }
  char type[2];
  readChar(source, type, 2);
  type[2] = '\0';

  uint32_t bmpSize = 69;
  readu32(source, &bmpSize);

  uint16_t spam1;
  read16(source, &spam1);

  uint16_t spam2;
  read16(source, &spam2);

  uint32_t offset;
  readu32(source, &offset);
  //header

  uint32_t headerSize;
  readu32(source, &headerSize);

  int32_t width;
  read32(source, &width);

  int32_t height;
  read32(source, &height);

  uint16_t colorPlanesNum;
  read16(source, &colorPlanesNum);

  uint16_t colors;
  read16(source, &colors);

  uint32_t compression;
  readu32(source, &compression);

  uint32_t raw;
  readu32(source, &raw);

  uint32_t pRes1;
  readu32(source, &pRes1);

  uint32_t pRes2;
  readu32(source, &pRes2);

  uint32_t numColPalette;
  readu32(source, &numColPalette);

  uint32_t impColors;
  readu32(source, &impColors);
  
  if( !(type[0] == 'B' && type[1] == 'M') )
  {
    close(source);
    errx(1, "This isn't a BMP file");
  }

  if( !(headerSize == 40) )
  {
    close(source);
    errx(2, "This isn't a BITMAPINFOHEADER.. I think");
  }

  if( !(colors == 24) )
  {
    close(source);
    errx(3, "Colors are %ibit and not 24bit", colors);
  }

  if( !(compression == 0) )
  {
    close(source);
    errx(4, "This image is compressed I guess");
  }
  
  if(width < 0)
  {
    width *= (-1);
  }  
  
  if(height < 0)
  {
    height *= (-1);
  }
// width and height in BMP can be negative

  if( !(height >= 20 && width >= 20) )
  {
    close(source);
    errx(5, "The image is too small");
  }
  
  if(height > 1650 || width > 1650)
  {
    close(source);
    errx(69, "I'm sorry but this program is too primitive to work with as large files. Here's a fancy error code instead.");
  }
// Header stored and checked
 
  int output;
  if( (output = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666)) == -1 )
  {
    close(source);
    errx(14, "I can't write here");
  }
// creates or rewrites file

  writeChar(source, output, type, 2);
  writeu32(source, output, &bmpSize);
  write16(source, output, &spam1);
  write16(source, output, &spam2);
  writeu32(source, output, &offset);
  writeu32(source, output, &headerSize);
  write32(source, output, &width);
  write32(source, output, &height);
  write16(source, output, &colorPlanesNum);
  write16(source, output, &colors);
  writeu32(source, output, &compression);
  writeu32(source, output, &raw);
  writeu32(source, output, &pRes1);
  writeu32(source, output, &pRes2);
  writeu32(source, output, &numColPalette);
  writeu32(source, output, &impColors);
// header is saved

  unsigned char buffer[1650][1650][3];
  uint8_t padding = width % 4;// defines how many bites of padding there are at the end of the pixel line due to how BMP works
  char spam[5];

  for(int32_t i = 0; i < height; i++)
  {
    if( (read(source, buffer[i], width * 3) ) != (width * 3)  )
    {
      close(output);
      close(source);
      errx(14, "Reading Error");
    }
    if( (read(source, spam, padding) ) != padding)
// cycles through the standard BMP padding    
    {
      close(output);
      close(source);
      errx(14, "Reading Error");
    }
  }
// file is stored

  drawingFunction(buffer, height, width, 5);
  bonusDrawing(buffer, height, width, 0, 0, 0);
  for(int32_t i = 0; i < height; i++)
  {
    if( (write(output, buffer[i], width * 3) ) != (width * 3) )
    {
      close(output);
      close(source);
      errx(16, "Writing Error after modifying");
    }
    if( (write(output, spam, padding) ) != padding )// writes the needed padding
    {
      close(output);
      close(source);
      errx(16, "Writing Error after modifying");
    }
  }
  close(source);
  close(output);
  return 0;
}
