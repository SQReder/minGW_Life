#ifndef MATRIX_TEMPL
#define MATRIX_TEMPL
#ifndef NULL
#define NULL 0
#endif

/* -----------------------------------------
 Ётот шаблон примен€ет к каждой €чейке матрицы функцию вида
 F func(T& value, unsigned int y, unsigned int x)
 value - ссылка на €чейку матрицы с координатами [y][x]
 ----------------------------------------- */
template <typename T, typename F>
void foreach_in_matrix(T** matrix, unsigned int w, unsigned int h, F func) {
	for (unsigned int y = 0; y < h; y++)
		for (unsigned int x = 0; x < w; x++)
			func(matrix[y][x], y, x);
};

/* -----------------------------------------
 Ўаблон дл€ выделени€ пам€ти под матрицу
 ----------------------------------------- */
template <typename T>
T** allocate_matrix(unsigned int w, unsigned int h) {
	T** matrix = new T *[h];
	for (unsigned int y = 0; y < h; y++)
		matrix[y] = new T[w];

	return matrix;
}

/* -----------------------------------------
 Ўаблон освобождени€ пам€ти
 усли destroy == true то дл€ каждого
 значени€ сначала вызываетс€ деструктор
 ----------------------------------------- */
template <typename T>
void delete_matrix(T** matrix, unsigned int h) {
	// если нулевой указатель - то выходим из функции - освобождать нечего
	if (matrix == NULL)
		return;

	// проходим по строкам матрицы
	for (unsigned int y = 0; y < h; ++y) {
		// освобождаем пам€ть от строки
		delete[]matrix[y];
	}

	// освобождаем указатель на строки
	delete[]matrix;
}

/* -----------------------------------------
 Ўаблон дл€ извлечени€ участка матрицы
 ----------------------------------------- */
template <typename T>
T** extract_matrix(T** src, unsigned int src_x, unsigned int src_y, unsigned int w, unsigned int h) {
	T** dst = allocate_matrix <T> (w, h);
	for (unsigned int y = 0; y < h; y++) {
		for (unsigned int x = 0; x < w; x++) {
			dst[y][x] = src[src_y + y][src_x + x];
		}
	}
	return dst;
}

/* -------------------------------------------
 Ўаблон нахождени€ среднего значени€ в матрице
 ------------------------------------------- */
template <typename T>
float avgf(T** matrix, unsigned int w, unsigned int h) {
	if (w * h == 0)
		throw;
	float summ = 0;
	for (unsigned int y = 0; y < h; y++)
		for (unsigned int x = 0; x < w; x++)
			summ += matrix[y][x];
	summ /= (float)(h* w);
	return summ;
};
#endif
