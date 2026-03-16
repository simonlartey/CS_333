# Bruce A. Maxwell
# Spring 2018
# PPM IO functions
#
# A simple PPM library for reading and writing color PPMs
#

import sys

class PPM:

    def __init__(self, filename=None):
        self.rows = 0
        self.cols = 0
        self.colors = 255
        self.data = []
        self.source = filename

        if filename != None:
            self.read(filename)

    def read( self, filename ):

        try:
            fp = open( filename, "rb" ) # open the file as a binary file

            s = ""
            c = fp.read(1)
            while c != b"\n":
                s += str(c)
                c = fp.read(1)

            if s == b'P'b'6':
                print("PPM Magic number")

            c = fp.read(1)
            while c == b"#":
                while c != b"\n":
                    c = fp.read(1)
                c = fp.read(1)

            s = ""
            while c != b"\n":
                s += c.decode("utf-8")
                c = fp.read(1)

            words = s.split()
            self.cols = int(words[0])
            self.rows = int(words[1])
            self.colors = int(words[2])

            print("Rows %d  Cols %d  Colors %d" % (self.rows, self.cols, self.colors))
            self.data = bytearray(fp.read()) # read the rest of it

            fp.close()

        except:
            print("Unable to process file %s" % (filename))
            return None


    def write( self, filename ):
        fp = open(filename, "wb")
        s = "P6\n%d %d %d\n" % (self.cols, self.rows, self.colors)
        fp.write( bytearray(s, encoding='utf-8' ) )
        fp.write( self.data )
        fp.close()

    def get( self, row, col ):
        index = 3 * (row * self.cols + col)
        return [self.data[index+0], self.data[index+1], self.data[index+2]]


    def set( self, row, col, r, g, b ):
        index = 3 * (row * self.cols + col)
        self.data[index+0] = r
        self.data[index+1] = g
        self.data[index+2] = b
        

def main(argv):
    if len(argv) < 2:
        print("Usage: python3 <image filename>")
        exit()

    print("Reading image", argv[1])
    ppm = PPM(argv[1])
    print("Setting values")
    ppm.set( 146, 163, 0, 0, 0)
    ppm.set( 147, 163, 0, 0, 0)
    ppm.set( 146, 164, 0, 0, 0)
    ppm.set( 147, 164, 0, 0, 0)
    print(ppm.get( 145, 160))
    print("Writing mod.ppm")
    ppm.write("mod.ppm")
    print("Terminating")


if __name__ == "__main__":
    main(sys.argv)
