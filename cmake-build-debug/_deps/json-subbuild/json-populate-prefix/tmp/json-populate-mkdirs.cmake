# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-src"
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-build"
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-subbuild/json-populate-prefix"
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-subbuild/json-populate-prefix/tmp"
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-subbuild/json-populate-prefix/src"
  "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/MyPathToGlory/My massive fucking project/search_engine/cmake-build-debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp/${subDir}")
endforeach()
