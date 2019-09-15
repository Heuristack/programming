
MAIN=HelloLilyPond.pdf
main:$(MAIN)

all: *.pdf

%.pdf: %.ly
	lilypond --format=pdf $<

.PHONY: clean show
clean:
	rm -rf *.pdf *.midi
show:
	open $(MAIN)

