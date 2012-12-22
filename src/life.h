#ifndef LIFE_H
#define LIFE_H

typedef char lType;

class tlife {
public:
	tlife(int w, int h);
	~tlife();

	void seed(int count);
	void step();

	const lType **get_grid() const ;

private:
	int w;
	int h;

	lType **grid;
	lType **buff;

	void process(int x, int y);
	int neighbour(int x, int y);

};
#endif
