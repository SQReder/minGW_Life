#ifndef MATRIX_TEMPL
#define MATRIX_TEMPL
#ifndef NULL
#define NULL 0
#endif

/* -----------------------------------------
 ���� ������ ��������� � ������ ������ ������� ������� ����
 F func(T& value, unsigned int y, unsigned int x)
 value - ������ �� ������ ������� � ������������ [y][x]
 ----------------------------------------- */
template <typename T, typename F>
void foreach_in_matrix(T** matrix, unsigned int w, unsigned int h, F func) {
	for (unsigned int y = 0; y < h; y++)
		for (unsigned int x = 0; x < w; x++)
			func(matrix[y][x], y, x);
};

/* -----------------------------------------
 ������ ��� ��������� ������ ��� �������
 ----------------------------------------- */
template <typename T>
T** allocate_matrix(unsigned int w, unsigned int h) {
	T** matrix = new T *[h];
	for (unsigned int y = 0; y < h; y++)
		matrix[y] = new T[w];

	return matrix;
}

/* -----------------------------------------
 ������ ������������ ������
 ���� destroy == true �� ��� �������
 �������� ������� ���������� ����������
 ----------------------------------------- */
template <typename T>
void delete_matrix(T** matrix, unsigned int h) {
	// ���� ������� ��������� - �� ������� �� ������� - ����������� ������
	if (matrix == NULL)
		return;

	// �������� �� ������� �������
	for (unsigned int y = 0; y < h; ++y) {
		// ����������� ������ �� ������
		delete[]matrix[y];
	}

	// ����������� ��������� �� ������
	delete[]matrix;
}

/* -----------------------------------------
 ������ ��� ���������� ������� �������
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
 ������ ���������� �������� �������� � �������
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
