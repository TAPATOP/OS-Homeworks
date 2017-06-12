Историята е на дъното.
void readChar(int source, char* input, uint8_t count)
[…]
void writeu32(int source, int output, uint32_t* array)
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Проверки за правилно четене/ писане. Причината да използвам функции е за да няма нужда да пиша проверките и затварянията на файловете всеки път.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void drawingFunction(unsigned char buffer[1650][1650][3], int32_t height, int32_t  width, uint8_t offset)
[…]
Функцията чертае правоъгълника.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if(argc != 3)
  {
    errx(11, "Give exactly two file names pls thx");
  }
  Проверка за валиден вход.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if( (source = open(argv[1], O_RDONLY) ) == -1)
  {
    errx(12, "I don't seem to be able to open or read from that :<");
  }
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Опит за отваряне на файл. При грешка програмата спира
  char type[2];
  readChar(source, type, 2);
[…]
  readu32(source, &impColors);
  Четене на целия header
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if( !(type[0] == 'B' && type[1] == 'M') )
  {
    close(source);
    errx(1, "This isn't a BMP file");
  }
[…]
  if( !(height >= 20 && width >= 20) )
  {
    close(source);
    errx(5, "The image is too small");
  } 
Проверка на целия header спрямо правилата и условията
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if(height > 1650 || width > 1650)
  {
    close(source);
    errx(69, "I'm sorry but this program is too primitive to work with as large files. Here's a fancy error code instead.");
  }
 Не успях да го направя с динамична памет, понеже пак гърмеше със segmentation fault
  int output;
  if( (output = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666)) == -1 )
  {
    close(source);
    errx(14, "I can't write here");
  }
// creates or rewrites file

  writeChar(source, output, type, 2);
[…]
  writeu32(source, output, &impColors);
Отваря файл и записва целия header.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  unsigned char buffer[1650][1650][3];
  uint8_t padding = width % 4;// defines how many bites of padding there are at the end of the pixel line due to how BMP works
  char spam[5];
Padding е с размера на добавените байтове на края на всеки ред в BMP файл с цел техният брой да е кратен на 4. За това и искаме остатъка от делене на 4. Използваме spam за да симулираме „празен оборот“
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  for(int32_t i = 0; i < height; i++)
  {
    if( (read(source, buffer[i], width * 3) ) == (width * 3) )
    {
      close(output);
      close(source);
      errx(14, "Reading Error");
    }
    if( (read(source, spam, padding) ) == padding)
// cycles through the standard BMP padding    
    {
      close(output);
      close(source);
      errx(14, "Reading Error");
    }
  }
Четем целия файл ред по ред, като ако има грешка- спираме. След края на всеки ред циклим напразно в зависимост от padding.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  for(int32_t i = 0; i < height; i++)
  {
    if( (write(output, buffer[i], width * 3) ) != (width * 3) )
    {
      close(output);
      close(source);
      errx(16, "Writing Error after modifying");
    }
    if( (write(output, spam, padding) ) != padding )// writes the needed padding
    {
      close(output);
      close(source);
      errx(16, "Writing Error after modifying");
    }
  }
Записваме файла, като ако настане грешка прекъсваме.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Историята е отдолу с повечето линкове, които съм използвал.
https://stackoverflow.com/questions/2307057/how-to-read-a-binary-file-in-c-video-images-or-text?answertab=votes#tab-top
https://stackoverflow.com/questions/12586658/getting-incorrect-values-from-a-bmp-file
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm
От тук разбрах, че 24-битовите изображения нямат Color Table
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
https://stackoverflow.com/questions/2423628/whats-the-difference-between-a-file-descriptor-and-file-pointer
https://stackoverflow.com/questions/14680232/how-to-detect-a-file-is-opened-or-not-in-c 
https://stackoverflow.com/questions/1968561/getting-the-pixel-value-of-bmp-file
https://stackoverflow.com/questions/11573974/write-to-txt-file
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
https://stackoverflow.com/questions/12240299/convert-bytes-to-int-uint-in-c
Първоначално четох целия header в буфер, от който извеждах данните от него чрез побитовите операции, показани в темата. По някаква причина даваха грешки в сметките и се наложи да ги чета едно по едно, директно
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Цялата работа по файла да се извършва със системни извиквания на ниско ниво - open(2), close(2), read(2), write(2)…
Като препрочетох това трябваше да пренапиша половината код… : (
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
https://stackoverflow.com/questions/2245193/why-does-open-create-my-file-with-the-wrong-permissions
заради това 5 часа заминаха ей тъй. Video related:
https://www.facebook.com/skillprogramming/videos/1947977792100438/
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

https://stackoverflow.com/questions/23092040/how-to-open-a-file-which-overwrite-existing-content
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
https://stackoverflow.com/questions/75191/what-is-an-unsigned-char
wtf. Не знаех, че съществува такова нещо
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
https://stackoverflow.com/questions/2601365/padding-in-24-bits-rgb-bitmap
Да, важно инфо…
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Прекарах половин час чудейки се защо новият файл е с 40В по- голям от оригиналния, докато не осъзнах, че го сравнявам с размера на друг…
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Премахнах два for-а и вместо да чета байт по байт чета всичко почти наведнъж. Скороста, разбира се, се увеличи масивно.
https://stackoverflow.com/questions/2128728/allocate-matrix-in-c
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
https://stackoverflow.com/questions/22850436/can-the-width-field-in-a-bmp-with-bitmapinfoheader-be-negative
Важно. Поне донякъде

