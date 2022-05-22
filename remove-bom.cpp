#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

namespace fs = std::filesystem;

static constexpr uint8_t BOM[] = { 0xef, 0xbb, 0xbf };
static constexpr size_t BOM_SIZE = sizeof( BOM ) / sizeof( uint8_t );

int main( int argc, char *argv[] )
{
  if ( ! fs::exists( argv[1] ) ) {
    cerr << "File is not exist" << endl;
    return -1;
  }

  size_t size = fs::file_size( argv[1] );

  if ( size < BOM_SIZE ) {
    cerr << "File size is too small" << endl;
    return -1;
  }

  uint8_t *data = new uint8_t[size];

  ifstream is( argv[1] );
  is.read( (char *)data, size );

  if ( strncmp( (char *)data, (char *)BOM, BOM_SIZE ) != 0 ) {
    cerr << "No UTF-8 BOM" << endl;
    delete [] data;
    return -1;
  }

  ofstream os( argv[2] );
  os.write( (char *)data + BOM_SIZE, size - BOM_SIZE );

  delete [] data;

  return 0;
}
