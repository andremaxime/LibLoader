#ifndef __LIBLOADER_HHP__
# define __LIBLOADER_HHP__

# include <iostream>
# include <dlfcn.h>

template <typename LibType>
class LibLoader
{
public:
  LibLoader(const std::string &entryName){
      this->entryName = entryName;
      this->_handle = NULL;
  }

  ~LibLoader(){
  }

private:
  void *_handle;

public:
  std::string entryName;

  LibType* openLib(const std::string &libName){
    if (_handle != NULL)
      dlclose(_handle);

    _handle = dlopen(libName.c_str(), RTLD_LAZY); // FLAG A ADAPTER SI BESOIN
    if (_handle == NULL)
      return NULL;
    LibType* (*external_creator)();
    external_creator = reinterpret_cast<LibType * (*)()>(dlsym(_handle, entryName.c_str()));
    if (external_creator == NULL)
      return NULL;
    return external_creator();
  }

  bool closeLib(){
    dlclose(_handle);
  }
};

#endif
