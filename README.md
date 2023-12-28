Generator of crypto wallets for:<br/>
<b><i>Bitcoin (BTC)</i></b><br/>
<b><i>Monero (XMR)</i></b><br/>
<b><i>Dogecoin (DOGE)</i></b><br/>
<b><i>Litecoin (LTC)</i></b><br/>
<b><i>Solana (SOL)</i></b><br/>
<br/>
Use SFML for it. In code you can to change <MyLib/...> includes.<br/>
<br/>
DONATE:<br/>

	XMR:
		87MnyP3mpxQBmCoQHM4H64RuaBZtP5zW2hGWu18YPujA94a18ypzpYT6jnNq68Q24yXwXAFDG2Vi91AgLNC76uEcR5WMoRp
	BTC:
		bc1qrg8agge2gcy75kct9g3cxeyl26ecjsx5wf4r8a
	DOGE:
		D9UD5v6xDAQZkBpJz1eP3Q1byGBC9dx5rd
	Litecoin:
		Latr7n7ATGEC9AGXbJW2D9SWQdQUu3am1C
  	Solana:
   		ET1Zbdun77T64e5EPBkyj13DZyLMmkjiB7nkVHak2q87
<br/>
<h1>Instruction (RUS):</h1><br/>
</br>
  Используемые репозитории:<br/>
        https://github.com/luigi1111/xmr.llcoins.net<br/>
        https://github.com/iancoleman/bip39<br/>
        https://github.com/OutCast3k/coinbin/<br/>
</br>
Замените в коде <i>#include &lang;MyLib/...&rang;</i> (с угловыми скоками) на <i>#include "MyLib/..."</i> (с кавычками), если не компилируется.</br>
Данный код собирался в Microsoft Visual Studio 2017. Вам неоходимо использовать SFML, эту библиотеку можно бесплатно скачать на https://www.sfml-dev.org/. После установки библиотеки используйте соответствующие dll для запуска exe (dll нужно поместить в папку с exe, либо в папку C:/WINDOWS/SysWOW64/ для Windows 7). Из-за медленной работы BigInteger в режиме Debug крайне рекомендуется собирать Release. Также замечу, что все мои вспомогательные библиотеки писались только под x64. Не забудьте настроить проект Visual Studio на использование SFML C++ за 3 минуты: https://www.youtube.com/watch?v=WD0czEmX3xE.<br/>
Если при сборке будет ругаться из-за строк <i>#pragma comment(lib, ...)</i>, уберите их.
</br>
<h2>Содание кошелька:</h2><br/>
01. Запустить exe.<br/>
02. Выбрать монету.<br/>
03. Ввести случайную строку и выбрать файл со случайными данными.<br/>
04. Водить мышкой и сгенерироввать файлы.<br/>
05. Сохранить файлы в KeePass, не открывать их ни в каких редакторах, кроме внутреннего встроенного просмотрщика KeePass.<br/>
06. Затереть файлы.<br/>
07. Создать кошельки ОФФЛАЙН:<br/>

  Для Bitcoin:<br/>
    
        01. Вставить seed в bip39.
        02. Подождать Calculating.
        03. Перейти в BIP84, все галочки оставить пустыми.
        04. Сохранить WIF и адрес в KeePass.
        
  Для Monero:<br/>
  
        01. Открыть xmr.llcoins.net.
        02. Вставить hex в addresstests.html (поле 2).
        03. Нажать Gen 1. и скопировать SEED.
        04. Открыть addressgen.html.
        05. Вставить SEED и нажать Generate.
        06. Сохранить SEED, Private View Key и адрес в KeePass.
        
  Для Dogecoin:<br/>
  
        01. Открыть coinbin.
        02. Перейти в Help->Settings.
        03. Выбрать Dogecoin.
        04. Нажать "Отправить".
        05. Перейти в New->Address.
        06. Отметить галочки "Compress (recommended)" и "Custom Seed or Brain Wallet".
            Галочку "Encrypt Private Key with AES-256 Password" не устанавливать.
        07. Вставить в поле строку кошелька из out_dog.txt.
        08. Нажать Generate.</br>
        09. Сохранить адрес и WIF в KeePass.</br>
        
  Для Litecoin:<br/>
  
        01. Открыть coinbin.
        02. Перейти в Help->Settings.
        03. Выбрать Litecoin.
        04. Нажать "Отправить".
        05. Перейти в New->Address.
        06. Отметить галочки "Compress (recommended)" и "Custom Seed or Brain Wallet".
            Галочку "Encrypt Private Key with AES-256 Password" не устанавливать.
        07. Вставить в поле строку кошелька из out_ltc.txt.
        08. Нажать Generate.
        09. Сохранить адрес и WIF в KeePass.

 Для Solana:<br/>

        01. Откройте приложение Solflare и восстановите кошелёк вашей SEED-фразой.
        02. Скопируйте адрес и (при желании) закрытый ключ кошелька.
        03. Сохраните всё в KeePass.
<br/>
<br/>
<h2>Отправка средств:</h2><br/>
  Для Monero:<br/>
    
        Через официальное приложение, можно через оффлайн подпись транзакции или
        лицензионным компьютером только с одним приложением Monero.

  Для Solana:
  	
        Как и при создании кошелька, войдите в Solflare и отправляйте монеты куда угодно.
        Там же можно стейкать любому валидатору.
 
  Для Bitcoin/Dogecoin/Litecoin:<br/>
    
        ОНЛАЙН:
            01. Открыть coinbin.
            02. Перейти в Help->Settings и выбрать монету.
            03. Выбрать New->Transaction.
            04. Вставить Адрес.
            05. Нажать Load.
            06. Заполнить Outputs и учесть комиссию. Актуальную комиссию можно взять с mempool.space.
            07. Нажать Submit. Сохранить строку в KeePass.
        ОФФЛАЙН:
            08. Открыть coinbin.
            09. Перейти в Help->Settings и выбрать монету.
            10. Перейти во вкладку Sign.
            11. Вставить WIF и текст из п. 07.
            12. Нажать Submit.
            13. Сохранить строку в KeePass.
        ОНЛАЙН:
            14. Открыть coinbin.
            15. Перейти в Help->Settings и выбрать монету.
            16. Перейти во вкладку Broadcast.
            17. Вставить текст из п. 13.
            18. Нажать Submit.
