filename = FIFO_2
in = input/${filename}.txt
out = output/${filename}_stdout.txt
dm = output/${filename}_dmesg.txt

main: main.o scheduling.o
	gcc main.o scheduling.o -o exe
main.o: main.c Makefile
	gcc main.c -c
scheduling.o: scheduling.c scheduling.h Makefile
	gcc scheduling.c -c
clean:
	rm -rf *o

run:	
	sudo ./exe
	
# 	sudo dmesg -c
# 	sudo ./exe < ${in} > ${out}
# 	dmesg | grep Project1 > ${dm}

# 	sudo dmesg -c
# 	sudo ./exe < input/TIME_MEASUREMENT.txt > output/TIME_MEASUREMENT_stdout.txt
# 	dmesg | grep Project1 > output/TIME_MEASUREMENT_dmesg.txt

# 	sudo dmesg -c
# 	sudo ./exe < input/FIFO_1.txt > output/FIFO_1_stdout.txt
# 	dmesg | grep Project1 > output/FIFO_1_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/FIFO_2.txt > output/FIFO_2_stdout.txt
# 	dmesg | grep Project1 > output/FIFO_2_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/FIFO_3.txt > output/FIFO_3_stdout.txt
# 	dmesg | grep Project1 > output/FIFO_2_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/FIFO_4.txt > output/FIFO_4_stdout.txt
# 	dmesg | grep Project1 > output/FIFO_2_dmesg.txt	
# 	sudo dmesg -c
# 	sudo ./exe < input/FIFO_5.txt > output/FIFO_5_stdout.txt
# 	dmesg | grep Project1 > output/FIFO_2_dmesg.txt

# 	sudo dmesg -c
# 	sudo ./exe < input/RR_1.txt > output/RR_1_stdout.txt
# 	dmesg | grep Project1 > output/RR_1_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/RR_2.txt > output/RR_2_stdout.txt
# 	dmesg | grep Project1 > output/RR_2_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/RR_3.txt > output/RR_3_stdout.txt
# 	dmesg | grep Project1 > output/RR_3_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/RR_4.txt > output/RR_4_stdout.txt
# 	dmesg | grep Project1 > output/RR_4_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/RR_5.txt > output/RR_5_stdout.txt
# 	dmesg | grep Project1 > output/RR_5_dmesg.txt

# 	sudo dmesg -c
# 	sudo ./exe < input/SJF_1.txt > output/SJF_1_stdout.txt
# 	dmesg | grep Project1 > output/SJF_1_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/SJF_2.txt > output/SJF_2_stdout.txt
# 	dmesg | grep Project1 > output/SJF_2_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/SJF_3.txt > output/SJF_3_stdout.txt
# 	dmesg | grep Project1 > output/SJF_3_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/SJF_4.txt > output/SJF_4_stdout.txt
# 	dmesg | grep Project1 > output/SJF_4_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/SJF_5.txt > output/SJF_5_stdout.txt
# 	dmesg | grep Project1 > output/SJF_5_dmesg.txt

# 	sudo dmesg -c
# 	sudo ./exe < input/PSJF_1.txt > output/PSJF_1_stdout.txt
# 	dmesg | grep Project1 > output/PSJF_1_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/PSJF_2.txt > output/PSJF_2_stdout.txt
# 	dmesg | grep Project1 > output/PSJF_2_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/PSJF_3.txt > output/PSJF_3_stdout.txt
# 	dmesg | grep Project1 > output/PSJF_3_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/PSJF_4.txt > output/PSJF_4_stdout.txt
# 	dmesg | grep Project1 > output/PSJF_4_dmesg.txt
# 	sudo dmesg -c
# 	sudo ./exe < input/PSJF_5.txt > output/PSJF_5_stdout.txt
# 	dmesg | grep Project1 > output/PSJF_5_dmesg.txt
