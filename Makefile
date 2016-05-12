makebt: taobtree.c Dictionary.c
	gcc taobtree.c -o taobtree libbt.a
	gcc Dictionary.c -o Dictionary libbt.a -lreadline 
	./taobtree	
	@echo "#!/bin/bash\n./Dictionary" > run.sh 
	chmod +x run.sh
	@echo "\n\nCai dat chuong trinh thanh cong!\nClick file run.sh hoac chay lenh $ ./run.sh de chay chuong trinh!\n"

run:
	./Dictionary	
clean:    
	rm -f taobtree soundex.dic word.dic Dictionary run.sh AnhViet.dic makebt Dictionary.o taobtree.o
