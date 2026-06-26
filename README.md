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

## Çeviri notları ve kısaltmalar

LCD ekrandaki sınırlı alan yüzünden bazı kelimeler kısaltılmıştır. Aşağıda sık karşılaşılanlar ve açıklamaları verilmiştir.

### Menü başlıkları

| Kısaltma | Açıklama |
|----------|----------|
| `Kilit` | Otomatik tuş kilidi |
| `TXSure` | TX Süre / TOT (Time-Out Timer) |
| `PilTas` | Pil tasarrufu |
| `PilGor` | Pil göstergesi |
| `KanGor` | Kanal göstergesi |
| `AcMes` | Açılış mesajı |
| `BLZmn` | Arka ışık zamanı |
| `BLMin` / `BLMax` | Arka ışık minimum / maksimum seviyesi |
| `BLTxRx` | Arka ışık TX/RX davranışı |
| `TXKil` | TX kilidi |
| `RXModu` | RX modu |
| `Sql` | Squelch (parazit kısma) |
| `SetGuc` | Güç seviyesi ayarı |
| `SetKon` | Kontrast ayarı |
| `SetTrs` | Ters (invert) ekran ayarı |
| `SetKil` | Kilit ayarı |
| `SetMet` | S-meter (sinyal göstergesi) stili ayarı |
| `SetGUI` | Arayüz yazı boyutu ayarı |
| `SetZmn` | Zamanlayıcı ayarı |
| `SetOff` | Uyku gecikmesi ayarı |
| `SetNFM` | Dar bant (NFM) ayarı |
| `PilKal` | Pil voltaj kalibrasyonu |
| `PilTip` | Pil tipi (1600 / 2200 / 3500 mAh) |
| `Sifir` | Fabrika ayarlarına sıfırlama |

### Alt menü değerleri

| Görünen | Anlamı |
|---------|--------|
| `AC` / `KAPALI` | Açık / Kapalı |
| `GENIS` / `DAR` | Geniş bant / Dar bant |
| `OZEL` | Özel (kullanıcı) güç seviyesi |
| `DUS 1` ... `DUS 5` | Düşük güç seviyeleri |
| `ORTA` | Orta güç |
| `YUKSEK` | Yüksek güç |
| `TUM` | Tüm açılış bilgileri (Türk bayrağı logosu modu) |
| `MESAJ` | Açılış mesajı metni |
| `VOLTAJ` | Pil voltajı |
| `SES` | Açılış sesi |
| `YOK` | Hiçbir şey gösterme |

### Diğer mesajlar

| Görünen | Anlamı |
|---------|--------|
| `HOSGELDIN` | Hoşgeldiniz |
| `BIRAK` | Bırak |
| `TUM TUSLARI` | Tüm tuşları |
| `CIKIS BAS` | Çıkış bas |
| `Turkce Surum` | Türkçe Sürüm |

> [!NOTE]
> "Kapalı" anlamında kısaltma kullanmak yerine **KAPALI** tam olarak yazılmıştır. Bu değişiklik firmware boyutunu yaklaşık **12 byte** artırmıştır; 64 KB limit içinde çok küçük bir farktır.

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
