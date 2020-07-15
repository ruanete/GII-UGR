for i in $(seq 1 19); do
  rm media5.5
  gcc -x assembler-with-cpp -D TEST=$i -no-pie media5.5.s -o media5.5
  printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./media5.5
done
