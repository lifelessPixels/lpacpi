OUTDIR	:= cmake-build

all:
	cmake -B $(OUTDIR)
	cmake --build $(OUTDIR)

run: all
	./$(OUTDIR)/lpacpi

clean:
	rm -rf $(OUTDIR)
