OUTPUT :=sterowanie-lazikiem

#*.hh dir
IDIR :=inc
#*.o dir
ODIR :=obj
#*.cpp dir
SDIR :=src

CC :=g++
CFLAGS :=-I$(IDIR) -W -Wall -pedantic

#*.hh
_DEPS := ObiektGeom.hh PowierzchniaMarsa.hh lacze_do_gnuplota.hh Kolory.hh Lazik.hh MacierzRotacji3D.hh definicje.hh macierz.hh wektor.hh
DEPS := $(patsubst %,$(IDIR)/%,$(_DEPS))

#*.o
_OBJ := main.o ObiektGeom.o PowierzchniaMarsa.o lacze_do_gnuplota.o Lazik.o
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))

__start__: obj dat  pliki_do_rysowania ./${OUTPUT}
	rm -f core.* core; ./${OUTPUT}

obj:
	mkdir obj

dat:
	mkdir dat

pliki_do_rysowania:
	mkdir pliki_do_rysowania


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f obj/* ./${OUTPUT} core.* core liki_do_rysowania/*



help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
