# 
# # #删除git clone的文件的git相关文件；
# 
# ##################################

#!/bin/bash

echo "find git"
find ./ -name *git*

echo "clean git"

find ./ -name .gitignore  | xargs rm -f

find ./ -name .git  | xargs rm -rf -f

echo "clean end"

find ./ -name *git*