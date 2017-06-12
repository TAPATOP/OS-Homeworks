void bonusDrawing(unsigned char image[1650][1650][3], int32_t height, int32_t width, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
  for(int32_t i = (height / 4); i <= 3 * (height / 4); i++)
  {
    image[i - 1][width/2][0] = BLUE;
    image[i - 1][width/2][1] = GREEN;
    image[i - 1][width/2][2] = RED;
  }
  for(int32_t i = (width / 4); i <= 3 * (width / 4); i++)
  {
    image[height / 2][i - 1][0] = BLUE;
    image[height / 2][i - 1][1] = GREEN;
    image[height / 2][i - 1][2] = RED;
  }
}

Единствената разлика с основната програма е горната функция. Тя приема като параметри файлът за обработка, височината и ширината му и желания цвят на рисунката( която е плюс/ кръст) във формат RGB. Файлът се извиква по същия начин. Няма ограничение откъм размер на файл, освен default-ния, който е 20х20.
