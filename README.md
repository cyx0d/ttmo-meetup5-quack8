# Quack-8 ve Quack-8'in Hikayesi
Selaamlaarr. Bu bölümde sizlere Quack-8'i yazmaya nasıl başladığımın ve Quack-8 isminin nereden geldiğini anlatacağım.
Akabinde Quack-8'in eksiklerine değinip README.md'yi kapatacağız.

# Nedir bu Quack-8 ?
Quack-8 tarafımca 2-3 hafta içinde tamamen meetup5 için yazılmış bir custom JIT örneğidir. (Bu haline JIT demek ne mümkün...)

# Quack-8'in yazılış hikayesi ve "Quack-8" isminin çıkışı
Aslında meetup5 duyurulduğunda Furkan (drafert) ile beraber bir konu bulup meetup'a kafa atıp sunmayı düşünmüştük.
O gece ikimizinde düşünmekten uyuyamadığına adım kadar eminim ^^. Geçen 1-2 günün ardından konu bulamadığımız için
vazgeçmeye karar verdik. 14 Eylül gecesi rüyalarımı hex formatı ile görmektense GCC ile compile edilmiş bir şekilde 
görmeye başladım. Aklıma neden GCC hakkında bir konu çıkarmıyoruz sorusu geldi. Sizce de GCC hakkında bir sunum yapılsaydı
çok tatlı olmaz mıydı? Neyse kalktığım gibi tahtama GCC hakkında tüm bildiklerimi yazıp çizmeye başladım ve gün öğleyi geçince
Onu aradım ve aklımda olan her şeyi anlatmaya başladım. Anlattıkça 1 ay içinde bunları yapmamızın imkansız olduğu daha da göze
batmaya başladı. Konuşmanın sonunda pwncollege üzerinden çözdüğümüz Yan85 sorularına benzer bir JIT bulup, onunla çıkmaya karar 
verdik. Tüm gece süren bir araştırmanın sonunda aradığım gibi custom JIT örneği bulamayınca kendim yazmaya karar verdim 
(Bu araştırma sürerken Furkan kesin bir şekilde gelemeyeceğinin haberini verdi :/). Bu andan sonra birçok kez pes etmek istedim
JIT'i yazmak ve bunu kısıtlı bir zaman içinde yapmak üstümde çok büyük bir yüktü. Eninde sonunda JIT bitti ve kime göstersem
"İsmi ne bunun?" sorusu ile karşı karşıya kaldım (değişkenlere bile isim bulamayan ben JIT için nasıl bir bulabilirdim ki).
JIT için isim bulmak için vakit kaybetmemek adına ingilizce sözlüğümü açıp gözüme ilk çarpan kelimeyi JIT'e isim yaptım.
Veeeee sonrası zaten "Quack-8" ismi ortaya çıkıverdi.
Bundan sonrasını bir çoğunuz tahmin edebiliyorsunuzdur. JIT yazıldı, isim bulundu vee finalde meetup5 başladı...

# Quack-8 ve Eksikleri
Öncelikle Quack-8 temelinde 7 farklı komut ve 4 farklı register barındırmaktadır.
Bu 7 farklı komutun 5 tanesi bir çoğumuzun da daha önceden birçok kez kullandığı 
matematiksel ifadeler (+, -, ^, |, &).
Bu ifadelerin eksiğine göz atıcak olursak; bu ifadeler sadece tek bir register üzerinden birbirleri ile etkileşime geçmektedir.
Örneğin: ```add b, 4``` ifadesi b register'ına 4 eklerken ```sdr b, 4 ; add b, b``` ifadesi hata vermektedir.
Çünkü Quack-8 register'ları tek seferlik kayıt eder ve iki register'ı aynı anda kullanıma açık değildir.
Bu Quack-8 için en büyük eksikliklerden biri gibi görünüyor (en azından şu anlık ^^).

SDA (Send Data to Address) komutu için eklenmesi gerekenlerden bahsetmek için bu kodun biraz daha evrimleşmesi gerekli. :)

Daha sayamacağım kadar eksik olduğunu biliyorum fakat en basit hali ile işlevli olabilmesi için bunlar şimdilik yeterli gibi duruyor.
(Zamanla eklemeler yapılacaktır.)
