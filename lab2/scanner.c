/************************************************************************
*file: Lab1_source.c
* These functions are declared in the include file "scanner.h".
*related files: none
*author: Denys Fedorchenko
*written: 19/11/2017
*last modified: 20/11/2017
************************************************************************/

#include "scanner.h"

//parses a csv string and sets values for SCAN_info sc
int parse(const char * buf, SCAN_INFO *sc, int id) {
	char buf2[20];
	int j, k, lim, c;
	float v;

	lim = strlen(buf);

	(*sc).id = id;

	//check for wrong format
	c = 0;
	for (j = 0; j < lim; j++) {
		if (buf[j] == ';') c++;
	}
	if (c != 6) {
		printf("\nERROR: cant add new scan, WRONG FORMAT\n");
		return -1;
	}

	//parsing
	j = -1;
	while (buf[++j] != ';' && j < lim) {
		buf2[j] = buf[j];
	}
	buf2[j] = '\0';
	strcpy((*sc).manufacturer, buf2);

	k = 0;
	while (buf[++j] != ';' && j < lim) {
		buf2[k++] = buf[j];
	}
	buf2[k] = '\0';
	strcpy((*sc).model, buf2);

	k = 0;
	while (buf[++j] != ';' && j < lim) {
		buf2[k++] = buf[j];
	}
	buf2[k] = '\0';
	k = atoi(buf2);
	(*sc).year = k;

	k = 0;
	while (buf[++j] != ';' && j < lim) {
		buf2[k++] = buf[j];
	}
	buf2[k] = '\0';
	v = atof(buf2);
	(*sc).price = v;

	k = 0;
	while (buf[++j] != ';' && j < lim) {
		buf2[k++] = buf[j];
	}
	buf2[k] = '\0';
	k = atoi(buf2);
	(*sc).x_size = k;

	k = 0;
	while (buf[++j] != ';' && j < lim) {
		buf2[k++] = buf[j];
	}
	buf2[k] = '\0';
	k = atoi(buf2);
	(*sc).y_size = k;

	k = 0;
	while (buf[++j] <= '9' && buf[j] >= '0' && j < lim) {
		buf2[k++] = buf[j];
	}
	buf2[k] = '\0';
	k = atoi(buf2);
	(*sc).amount = k;

	return 0;
}

//creates a .db file using .csv file of SCAN_INFO data
int create_db(const char* csv, const char *db) {
	FILE *csvFile = NULL, *dbFile = NULL;
	char buf[256];
	int i;
	SCAN_INFO sc;

	csvFile = fopen(csv, "r");
	dbFile = fopen(db, "wb");
	if (csvFile == NULL) return -1;
	if (dbFile == NULL) return -1;
	//count amount of printers in csv file
	i = 0;
	while (!feof(csvFile)) {
		fgets(buf, 255, csvFile);
		i++;
	}

	fwrite(&i, sizeof(int), 1, dbFile);
	
	fseek(csvFile, 0, SEEK_SET);

	i = 0;//here we use i as id
	while (!feof(csvFile)) {
		fgets(buf, 255, csvFile);

		if(parse(buf, &sc, i) == 0) 
			fwrite(&sc, sizeof(sc), 1, dbFile);

		i++;
	}

	fclose(csvFile);
	fclose(dbFile);

	return 0;
}

//prints .db file on screen in readable format
void print_db(const char *db) {
	FILE *dbFile = NULL;
	int i;
	SCAN_INFO sc;

	dbFile = fopen(db, "rb");

	if (dbFile == NULL) {
		printf("ERROR");
		return;
	}

	fread(&i, sizeof(int), 1, dbFile);
	printf("\n\t\t\tSCANINFO\n");
	while (fread(&sc, sizeof(sc), 1, dbFile) != 0) {
		printf("ID: %4d | %10s | %20s | %dx%d | %8.2f | %5d |\n", sc.id, sc.manufacturer, sc.model, sc.x_size, sc.y_size, sc.price, sc.amount);
	}
	printf("\n");

	fclose(dbFile);
}

//additional function to make code for make_index shorter
void swap(char *x, char *y, int *a, int *b) {
	int it;

	it = *x;
	*x = *y;
	*y = it;
	it = *a;
	*a = *b;
	*b = it;
}

//create .idx file for given field_name
int make_index(const char *db, const char *field_name) {
	FILE *dbFile = NULL, *idx = NULL;
	SCAN_INFO *Arr;
	int *A;
	int i, j, k, s;
	float ft;
	char ct[20];
	char idxName[30];

	//formind field_name.idx filename
	strcpy(idxName, field_name);
	strcat(idxName, ".idx");

	idx = fopen(idxName, "wb");
	if (idx == NULL) return 0;
	dbFile = fopen(db, "rb");
	if (dbFile == NULL) return 0;
	fread(&i, sizeof(int), 1, dbFile);

	A = malloc(i * sizeof(int));
	Arr = malloc(i * sizeof(SCAN_INFO));
	i = -1;
	while (fread(&(Arr[++i]), sizeof(Arr[0]), 1, dbFile) != 0) {}
	k = i - 1;
	for (i = 0; i <= k; i++)
		A[i] = i;

	//sortings for different field_names
	//yeah, it is ugly, I know
	if (strcmp(field_name, "manufacturer") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (strcmp(Arr[j].manufacturer, Arr[j + 1].manufacturer) > 0) {
					strcpy(ct, Arr[j].manufacturer);
					strcpy(Arr[j].manufacturer, Arr[j + 1].manufacturer);
					strcpy(Arr[j + 1].manufacturer, ct);
					s = A[j];
					A[j] = A[j + 1];
					A[j + 1] = s;
				}
				else if (strcmp(Arr[j].manufacturer, Arr[j + 1].manufacturer) == 0) {
					if (strcmp(Arr[j].model, Arr[j + 1].model) > 0) {
						strcpy(ct, Arr[j].model);
						strcpy(Arr[j].model, Arr[j + 1].model);
						strcpy(Arr[j + 1].model, ct);
						s = A[j];
						A[j] = A[j + 1];
						A[j + 1] = s;
					}
				}
			}
		}
	}
	else if (strcmp(field_name, "model") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (strcmp(Arr[j].model, Arr[j + 1].model) > 0) {
					strcpy(ct, Arr[j].model);
					strcpy(Arr[j].model, Arr[j + 1].model);
					strcpy(Arr[j + 1].model, ct);
					s = A[j];
					A[j] = A[j + 1];
					A[j + 1] = s;
				}
			}
		}
	}
	else if (strcmp(field_name, "id") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (Arr[j].id > Arr[j + 1].id) {
					swap(&Arr[j].id, &Arr[j + 1].id, &A[j], &A[j + 1]);
				}
			}
		}
	}
	else if (strcmp(field_name, "year") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (Arr[j].year > Arr[j + 1].year) {
					swap(&Arr[j].year, &Arr[j + 1].year, &A[j], &A[j + 1]);
				}
				else if (Arr[j].year == Arr[j + 1].year) {
					if (Arr[j].id > Arr[j + 1].id) {
						swap(&Arr[j].year, &Arr[j + 1].year, &A[j], &A[j + 1]);
					}
				}
			}
		}
	}
	else if (strcmp(field_name, "amount") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (Arr[j].amount > Arr[j + 1].amount) {
					swap(&Arr[j].amount, &Arr[j + 1].amount, &A[j], &A[j + 1]);
				}
				else if (Arr[j].amount == Arr[j + 1].amount) {
					if (Arr[j].id > Arr[j + 1].id) {
						swap(&Arr[j].amount, &Arr[j + 1].amount, &A[j], &A[j + 1]);
					}
				}
			}
		}
	}
	else if (strcmp(field_name, "x_size") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (Arr[j].x_size > Arr[j + 1].x_size) {
					swap(&Arr[j].x_size, &Arr[j + 1].x_size, &A[j], &A[j + 1]);
				}
				else if (Arr[j].x_size == Arr[j + 1].x_size) {
					if (Arr[j].id > Arr[j + 1].id) {
						swap(&Arr[j].x_size, &Arr[j + 1].x_size, &A[j], &A[j + 1]);
					}
				}
			}
		}
	}
	else if (strcmp(field_name, "y_size") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (Arr[j].y_size > Arr[j + 1].y_size) {
					swap(&Arr[j].y_size, &Arr[j + 1].y_size, &A[j], &A[j + 1]);
				}
				else if (Arr[j].y_size == Arr[j + 1].y_size) {
					if (Arr[j].id > Arr[j + 1].id) {
						swap(&Arr[j].y_size, &Arr[j + 1].y_size, &A[j], &A[j + 1]);
					}
				}
			}
		}
	}
	else if (strcmp(field_name, "price") == 0) {
		for (i = 0; i < k; i++) {
			for (j = 0; j < k - i; j++) {
				if (Arr[j].price > Arr[j + 1].price) {
					ft = Arr[j].price;
					Arr[j].price = Arr[j + 1].price;
					Arr[j + 1].price = ft;
					s = A[j];
					A[j] = A[j + 1];
					A[j + 1] = s;
				}
				else if (Arr[j].price == Arr[j + 1].price) {
					if (Arr[j].id > Arr[j + 1].id) {
						ft = Arr[j].price;
						Arr[j].price = Arr[j + 1].price;
						Arr[j + 1].price = ft;
						s = A[j];
						A[j] = A[j + 1];
						A[j + 1] = s;
					}
				}
			}
		}
	}
	else {
		printf("\nERROR field %s is not a part of SCAN_INFO!!\n", field_name);
		return 0;
	}

	fwrite(A, sizeof(int), k + 1, idx);

	fclose(dbFile);
	fclose(idx);

	free(A);
	free(Arr);

	return 1;
}

//calls make)index for every field in SCAN_INFO
void reindex(const char *db) {
	make_index(db, "id");
	make_index(db, "manufacturer");
	make_index(db, "year");
	make_index(db, "model");
	make_index(db, "price");
	make_index(db, "x_size");
	make_index(db, "y_size");
	make_index(db, "amount");
}

//deletes a scan with given id from .db file
void del_scanner(const char *db, int id) {
	FILE *dbFile = NULL;
	SCAN_INFO sc;
	int i, ind, found;

	dbFile = fopen(db, "rb+");
	if (dbFile == NULL) return;

	fread(&i, sizeof(int), 1, dbFile);
	ind = 0;
	found = 0;
	//finding scan with given id in file
	while (fread(&sc, sizeof(sc), 1, dbFile) != 0) {
		if (sc.id == id) {
			found = 1;
			break;
		}
		ind++;
	}
	if (found == 0) {
		printf("\nERROR: scan with id %d is not a part of DB, INVALID ID\n", id);
		fclose(dbFile);
		return;
	}
	//next we write last scan on the place of deleted and resize file
	fseek(dbFile, 0, SEEK_SET);
	i--;
	fwrite(&i, sizeof(int), 1, dbFile);
	fseek(dbFile, sizeof(int) + i * sizeof(SCAN_INFO), SEEK_SET);
	fread(&sc, sizeof(sc), 1, dbFile);
	fseek(dbFile, (sizeof(int) + sizeof(SCAN_INFO) * ind), SEEK_SET);
	fwrite(&sc, sizeof(sc), 1, dbFile);
	_chsize(_fileno(dbFile), (sizeof(int) + i*sizeof(SCAN_INFO)));
	fclose(dbFile);
	reindex(db);
}

//add scan, given in csv format to .db file
void add_scanner(const char *db, const char* scanner_str) {
	FILE *dbFile = NULL;
	SCAN_INFO sc;
	int i, id = 0;

	dbFile = fopen(db, "rb+");
	if (dbFile == NULL) return;
	fread(&i, sizeof(int), 1, dbFile);

	//finding valid id
	while (fread(&sc, sizeof(sc), 1, dbFile) != 0) {
		if (sc.id > id) id = sc.id + 1;
	}

	if (parse(scanner_str, &sc, id) == 0) {
		_chsize(_fileno(dbFile), sizeof(int) + sizeof(SCAN_INFO) * (i + 1));
		fwrite(&sc, sizeof(SCAN_INFO), 1, dbFile);
	}

	fclose(dbFile);
}

//forms RECORD_SET for given indx_field using .idx files
RECORD_SET * get_recs_by_index(const char *dba, char *indx_field) {
	RECORD_SET *rs = NULL;
	FILE *idx , *dbFile;
	char idxName[30];
	int n, i;
	int *L;

	dbFile = fopen(dba, "rb");
	if (dbFile == NULL) return NULL;
	strcpy(idxName, indx_field);
	strcat(idxName, ".idx");
	idx = fopen(idxName, "rb");
	if (idx == NULL) return NULL;

	fread(&n, sizeof(int), 1, dbFile);

	L = malloc(sizeof(int) * n);
	if (fread(L, sizeof(int), n, idx) == 0) return NULL;
	rs = malloc(sizeof(RECORD_SET));
	rs->rec_nmb = n;
	rs->recs = malloc(sizeof(SCAN_INFO) * n);

	for (i = 0; i < n; i++) {
		fseek(dbFile, sizeof(int) + sizeof(SCAN_INFO) * L[i], SEEK_SET);
		fread(&(rs->recs[i]), sizeof(SCAN_INFO), 1, dbFile);
	}

	free(L);
	fclose(dbFile);
	fclose(idx);

	return rs;
}

//forms a RECORD_SET of scans, which fields match given value
RECORD_SET* select(const char *db, const char *field, const char *value) {
	RECORD_SET *rs = NULL;
	SCAN_INFO sc;
	FILE *dbFile;
	int n, add;//add  is a flag, shows whether current sc has to be added to rs, makes code much shorter

	dbFile = fopen(db, "rb");
	if (dbFile == NULL) return NULL;

	rs = malloc(sizeof(RECORD_SET));
	rs->rec_nmb = 0;
	rs->recs = NULL;

	fseek(dbFile, sizeof(int), SEEK_SET);

	n = 0;
	add = 0;
	while (fread(&sc, sizeof(SCAN_INFO), 1, dbFile) != 0) {
		if (strcmp(field, "manufacturer") == 0) {
			if (strcmp(sc.manufacturer, value) == 0) add = 1;
		}
		else if (strcmp(field, "model") == 0) {
			if (strcmp(sc.model, value) == 0) add = 1;
		}
		else if (strcmp(field, "id") == 0) {
			if (sc.id == atoi(value)) add = 1;
		}
		else if (strcmp(field, "year") == 0) {
			if (sc.year == atoi(value)) add = 1;
		}
		else if (strcmp(field, "amount") == 0) {
			if (sc.amount == atoi(value)) add = 1;
		}
		else if (strcmp(field, "x_size") == 0) {
			if (sc.x_size == atoi(value)) add = 1;
		}
		else if (strcmp(field, "y_size") == 0) {
			if (sc.y_size == atoi(value)) add = 1;
		}
		else if (strcmp(field, "price") == 0) {
			if (sc.price == atof(value)) add = 1;
		}
		else {
			printf("\nERROR: invalid field %s\n", field);
			return NULL;
			free(rs);
		}
		if (add == 1) {
			n++;
			rs->recs = realloc(rs->recs, sizeof(SCAN_INFO) * n);
			rs->recs[n - 1] = sc;
			add = 0;
		}
	}

	fclose(dbFile);
	if (n == 0) {
		free(rs);
		return NULL;
	}
	rs->rec_nmb = n;

	return rs;
}

//prints a record set...
void print_rec_set(RECORD_SET *rs) {
	int i;
	printf("\n\t\t\tRECORDSET\n");
	for(i = 0; i < rs->rec_nmb; i++) {
		printf("ID: %4d | %10s | %20s | %dx%d | %8.2f | %5d |\n", rs->recs[i].id, rs->recs[i].manufacturer, rs->recs[i].model, rs->recs[i].x_size, rs->recs[i].y_size, rs->recs[i].price, rs->recs[i].amount);
	}
	printf("\n");

}