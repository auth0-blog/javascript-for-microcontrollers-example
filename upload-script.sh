#/bin/sh

cat test.js | nc $1 65500 & 
PID=$!
sleep 2
kill $PID
