
modules="$(find . -type f -iname 'generated/module/appletvos/*.so')"

for module in ${modules}
do
    #echo ${module}
    codesign -s "James Folk" ${module}
done

modules="$(find . -type f -iname 'generated/module/ios/*.so')"

for module in ${modules}
do
    #echo ${module}
    codesign -s "James Folk" ${module}
done
