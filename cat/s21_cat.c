#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int opt;
  int flag = 0;

  int option_index = 0;

  while ((opt = getopt_long(argc, argv, "entsbvET", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'e':
        for (int i = 0; i < argc - 2; i++) {
          cat_e(argv[2 + i]);
        }
        flag = 1;
        break;
      case 'n':
        for (int i = 0; i < argc - 2; i++) {
          cat_n(argv[2 + i]);
        }
        flag = 1;
        break;
      case 't':
        for (int i = 0; i < argc - 2; i++) {
          cat_t(argv[2 + i]);
        }
        flag = 1;
        break;
      case 's':
        for (int i = 0; i < argc - 2; i++) {
          cat_s(argv[2 + i]);
        }
        flag = 1;
        break;
      case 'b':
        for (int i = 0; i < argc - 2; i++) {
          cat_b(argv[2 + i]);
        }
        flag = 1;
        break;
      case 'v':
        for (int i = 0; i < argc - 2; i++) {
          cat_v(argv[2 + i]);
        }
        flag = 1;
        break;
      case 'E':
        for (int i = 0; i < argc - 2; i++) {
          cat_E(argv[2]);
        }
        flag = 1;
        break;
      case 'T':
        for (int i = 0; i < argc - 2; i++) {
          cat_T(argv[2]);
        }
        flag = 1;
        break;
      default:
        printf("ERROR");
        opt = -1;
        break;
    }
  }
  if (flag != 1) {
    for (int i = 0; i < argc - 1; i++) {
      cat(argv[1 + i]);
    }
  }

  return 0;
}
/**
 * @brief Отображение файла
 *
 * @param name Имя файла
 */
void cat(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char line[256];
    while (fgets(line, sizeof(line), file)) {
      printf("%s", line);
    }
    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief Подсчет и печать количества строк файла
 *
 * @param name Имя файла
 */
void cat_n(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char line[256];
    int linenumber = 1;

    while (fgets(line, sizeof(line), file)) {
      printf("%6d\t%s", linenumber, line);
      linenumber++;
    }
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
  fclose(file);
}
/**
 * @brief -b Подсчет и печать количества не пустык строк файла
 *
 * @param name Имя файла
 */
void cat_b(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char line[256];
    int linenumber = 1;

    while (fgets(line, sizeof(line), file)) {
      if (line[0] != '\n' && line[0] != '\0') {
        printf("%6d\t%s", linenumber, line);
        linenumber++;
      } else {
        printf("%s", line);
      }
    }
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
  fclose(file);
}
/**
 * @brief -t Отображает табы ^I, замена непечатных символов
 *
 * @param name Имя файла
 */
void cat_t(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char c;
    while ((c = fgetc(file)) != EOF) {
      if (c == '\n') {
        putchar(c);
      } else {
        print_encodings(c);
      }
    }

    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief -s Объединение пробельных строк файла
 *
 * @param name Имя файла
 */
void cat_s(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char line[256];
    int flag = 0;
    while (fgets(line, sizeof(line), file)) {
      if (line[0] == '\n') {
        if (flag != 1) {
          printf("%s", line);
          flag = 1;
        }
      } else {
        printf("%s", line);
        flag = 0;
      }
    }
    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief -e Указание $ конца строки файла, замена непечатных символов
 *
 * @param name Имя файла
 */
void cat_e(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char c;
    while ((c = fgetc(file)) != EOF) {
      if (c == '\n') {
        printf("$");
        putchar(c);
      } else if (c != '\t') {
        print_encodings(c);
      } else {
        putchar(c);
      }
    }

    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief -v Замена непечатных символов
 *
 * @param name Имя файла
 */
void cat_v(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char c;
    while ((c = fgetc(file)) != EOF) {
      if (c == '\n') {
        putchar(c);
      } else if (c == '\t') {
        putchar(c);
      } else {
        print_encodings(c);
      }
    }

    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief -E Указание $ конца строки файла
 *
 * @param name Имя файла
 */

void cat_E(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char c;
    while ((c = fgetc(file)) != EOF) {
      if (c == '\n') {
        printf("$\n");

      } else {
        putchar(c);
      }
    }

    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief -T Отображает табы ^I
 *
 * @param name Имя файла
 */
void cat_T(char *name) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    char c;
    while ((c = fgetc(file)) != EOF) {
      if (c == '\t') {
        printf("^I");

      } else {
        putchar(c);
      }
    }

    fclose(file);
  } else {
    printf("Ошибка открытия файла: %s\n", name);
  }
}
/**
 * @brief Функция замены непечатного символа
 *
 * @param a Символ из файла
 */
void print_encodings(char a) {
  int c = (unsigned char)a;
  if (c > 127 && c < 160) {
    printf("M-^%c", c - 64);
  } else if (c < 32 && c != '\n') {
    printf("^%c", c + 64);
  } else if (c == 127) {
    printf("^?");
  } else {
    putchar(a);
  }
}