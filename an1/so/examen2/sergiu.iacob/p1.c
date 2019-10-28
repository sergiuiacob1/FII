/*******************************************************************************************************
Enunt prima problema:

a) Ce reprezinta cel de-al doilea parametru al functiei open()?
b) Dati un exemplu de apel al functiei open() pentru a obtine un descriptor la fisierul "fisier.txt" 
pentru scriere incepand cu sfarsitul acestuia.
(orice se va scrie va fi adaugat la finalul fisierului fara a suprascrie continutul anterior)

NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
*******************************************************************************************************/
a) Cel de-al doilea parametru reprezinta modul in care fisierul specificat ca primul parametru sa fie deschis: pentru citire, pentru scriere, pentru ambele etc. (ex: O_RDONLY, O_RDWR etc.)
b)
int fd;
fd = open ("fisier.txt", O_WRONLY);//il deschidem pentru scriere
lseek (fd, 0, SEEK_END);//mutam pointerul la sfarsit, pentru a scrie incepand cu sfarsitul acestuia

