g++ -c functions.cpp search_engine.cpp project.cpp; 
g++ -o myprogram functions.o search_engine.o project.o;
./myprogram;
string=`cat link.txt`;
if [[ $string == "BAD INPUT" ]]
then
  echo 
else
  xdg-open $string > /dev/null; 
fi
