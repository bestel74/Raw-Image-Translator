/*
  
	Written in 2016 by Steven Valsesia <steven.valsesia@gmail.com>

	Convert 24-bit RGB pixels to 16-bit BGR565 pixels

      	RawImageTranslator file.rgb888 file.bgr565

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	FILE *input, *output;
	unsigned long input_l=0, i=0;
	unsigned short bgr565;
	unsigned char buf[3], red, green, blue;

	if(argc < 3) {
		printf("Usage: %s [input RGB888] [output BGR565]\n", argv[0]);
		return 0; 
	}

	input = fopen(argv[1], "r");
	if(input == NULL) {
		perror("fopen");
		return -1;
	}

	output = fopen(argv[2], "w");
	if(output == NULL) {
		perror("fopen");
		fclose(input);
		return -1;
	}

	// Get input file length
	rewind(input);
	fseek(input, 0, SEEK_END);
	input_l = ftell(input);
	rewind(input);

	for(i=0 ; i < input_l ; i+=3) {
		fread(buf, 1, 3, input);
		red = buf[0];
        green = buf[1];
        blue = buf[2];

        bgr565 = (unsigned short)(blue * 31.0 / 255.0) |
                 (unsigned short)(green * 63.0 / 255.0) << 5 |
                 (unsigned short)(red * 31.0 / 255.0) << 11;

		fwrite(&bgr565, 2, 1, output);
	}
	
	printf("Done, %s : %ld bytes\n", argv[2], ftell(output));
	printf("Have fun\n");

	fclose(input);
	fclose(output);

	return 0;
}
