# UV-K5/K6/5R Türkçe Firmware

Bu proje, [armel/uv-k5-firmware-custom](https://github.com/armel/uv-k5-firmware-custom) (F4HWN özelleştirmesi) çatalının Türkçe arayüz ile yerelleştirilmiş halidir.

## Bu fork'ta neler değişti?

- **Tam Türkçe arayüz çevirisi** yapıldı.
- Açılıştaki sürüm yazısı artık **"Turkce Surum"** olarak görünüyor.
- Açılış ekranına **Tam ekran Türk bayrağı** logosu eklendi (Power-On Message **TÜM** modunda).
- Menülerde ve alt menü değerlerinde teknik kısaltmalar (DCS, CTCSS, RX/TX, PTT, VOX vb.) korundu.

> [!NOTE]
> Radyonun LCD fontu yalnızca 7-bit ASCII karakterleri desteklediği için Türkçe karakterler (ç, ğ, ı, ö, ş, ü, İ) ASCII karşılıklarıyla yazılmıştır. Örneğin:
> - `Güç` → `Guc`
> - `Tüm` → `Tum`
> - `Sürüm` → `Surum`
> - `Hoşgeldin` → `Hosgeldin`

## Çevrilen menüler ve ekranlar

Aşağıdaki kaynak dosyalar Türkçeleştirilmiştir:

| Dosya | Açıklama |
|-------|----------|
| `ui/menu.c` | Ana menü etiketleri ve alt menü değerleri |
| `ui/main.c` | Ana ekran / VFO göstergeleri |
| `ui/welcome.c` | Açılış (welcome) ekranı |
| `ui/fmradio.c` | FM radyo ekranı |
| `ui/aircopy.c` | Air Copy (veri kopyalama) ekranı |
| `ui/lock.c` | Tuş kilidi ekranı |
| `ui/helper.c` | Genel yardımcı mesajlar |
| `ui/scanner.c` | Tarayıcı (scanner) ekranı |
| `app/breakout.c` | Breakout oyunu ekranları |

Ayrıca `ui/menu.h` içindeki `gSubMenu_TXP` dizisi Türkçe güç seviyesi metinlerine uygun şekilde genişletildi.

## Türk bayrağı logosu

- `logo_bitmap.inc` dosyası 128×64 piksel monokrom Türk bayrağı bitmap'ini içerir.
- Bayrak logosu, menüden **AcMes** (Açılış Mesajı) seçeneği **TÜM** yapıldığında açılışta tam ekran gösterilir.
- **Mesaj** modunda ise metin tabanlı açılış ekranı görünür ve alt kısımda **"Turkce Surum"** yazar.
- Diğer modlarda (Voltaj, Ses, Yok) ilgili bilgiler görünür.

## Derleme

Docker imajı daha önce oluşturulmadıysa önce şu komutla oluşturun:

```powershell
docker build -t uvk5 .
```

Ardından firmware'i derlemek için:

```powershell
docker run --rm -v ${PWD}:/app -w /app uvk5 make
```

> Git Bash kullanıyorsanız MSYS yol dönüşümünü devre dışı bırakmak gerekebilir:
> ```bash
> MSYS_NO_PATHCONV=1 docker run --rm -v "C:/Users/KULLANICI/source/uv-k5-firmware-custom:/app" -w /app uvk5 make
> ```

Derleme sonucunda `f4hwn.packed.bin` dosyası oluşur; bu dosyayı radyonuza yükleyin.

## Uyarı

Bu firmware radyonuzu kullanılamaz hale getirebilir (brick). Yüklemeden önce EEPROM yedeği almanız önerilir. Tüm sorumluluk size aittir.
