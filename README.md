# Magic Cat at Hogwarts - 22028155

## Tổng quan

- Dựa trên Desgin, Sound và Cốt truyện từ Magic Cat Academy (Google Doodle Halloween 2016) và cảm hứng từ các Spells trong Harry Potter, đã sáng tạo ra game mới: Magic Cat at Hogwarts.
- Slide Powerpoint về game: https://54q13n-my.sharepoint.com/:p:/g/personal/thebeo2004_54q13n_onmicrosoft_com/EezwG1EZivhAscrlTUYjtzcBPCky4jdsBwPl-pDQMQCr-w?e=1zx1AE
- Các class và mối liên hệ: https://drive.google.com/file/d/1JKO8PQJSLlER42UcoKAoouGws_fcP4P-/view?usp=sharing
- Video demo game: https://www.youtube.com/watch?v=Sfx08pLlPts
- Game resources: https://www.spriters-resource.com/browser_games/googledoodles/sheet/108799/, https://www.youtube.com/watch?v=j_Ys8IWzyH0 (Sound of Top 10 Spells at Harry Potter)
- Tài liệu học tập: phattrienphanmemaz123, lazyfoo.

## Chi tiết chơi game

### Giao diện mở đầu:

<img width="404" alt="image" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/b33c5b2f-5cc6-4678-be36-3efec21e8052">

### Giao diện chơi game

<img width="406" alt="image" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/0656b78a-8e27-4c9a-819f-350d92e6b919">

- Trạng thái máu: Số hình trái tim phía trái trên.
- Trạng thái Expecto: Số lần ngọn lửa.
- Trạng thái Wingardium: Hình cơn lốc. Nếu cơn lốc xuất hiện thì được dùng Wingardium, còn không thì chưa thể dùng.
- Điểm số: Phía phải trên.

#### Phương thức chơi game

- Normal Attack: Di chuột đến nhần vào các Threats. Mỗi lần nhấn -1 máu threats. Số máu Threats hiển thị phía trên đỉnh đầu.
- Expecto Patronum: Nhấn giữ phím Ctrl trong 2,5s (Đọc thần chú), sau đó triệu hồi sấm đánh toàn thể Threats 1 máu. Ban đầu Bonus 1 lần dùng, sau đó cứ mỗi lần giết 15 threats thì +1 Expecto:
<img width="760" alt="Screenshot 2023-04-26 103518" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/c769567a-1829-4b13-95fe-0f79a70e4144">
<img width="756" alt="Screenshot 2023-04-26 103552" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/5bdb7470-bce8-4907-bb37-17611f4a55d3">
- Wingardium Leviosa: Nhấn giữ phím Alt trong 1.3s (Đọc thần chú), sau đó thổi bay toàn thể Threats ra xa. Số lần dùng vô hạn nhưng thời gian hồi 2.5s
<img width="760" alt="Screenshot 2023-04-26 104153" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/44c756f7-b40d-4d9c-aa40-d4eec8f0876e">
<img width="760" alt="Screenshot 2023-04-26 104242" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/9bad8243-e742-4729-85bb-424fef27249f">
- Stupefy: Có tác dụng hồi máu. Xuất hiện khi mất một lượng máu nhất định dưới dạng hình con mèo cute phía phải màn hình. Và phải nhấn vào con mèo đó.
<img width="757" alt="Screenshot 2023-04-26 104746" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/6a5e93b4-406b-4707-8f69-810f818b2c93">
<img width="759" alt="Screenshot 2023-04-26 104813" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/d29f4090-051e-41f9-b897-3fe9aceeea7c">

#### Cách tính điểm
- Khi giết một threat, thì điểm số giết được sẽ tỷ lệ thuận với khoảng cách từ đó đến Main.
- Nhân với hệ số: Là số Threats giết được cùng 1 lúc.
- Hệ số sẽ hiển thị ở bên dưới màn hình khi giết >= 1 threat.

### Giao diện kết thúc game
- Game được chia ra làm 15 đợt Threats. Mỗi đợt sẽ có lượng Threats nhất định và mạng của mỗi threats từ 1 -> 2.
- Càng về sau, lượng Therats càng nhiều, mạng của chúng càng nhiều, càng khó chơi.
- Sau khi diệt hết Threats thì sẽ kết thúc game: Sẽ có Your Score và High Score.
- Còn nếu bạn bị giết lúc chơi thì cũng kết thúc game.

<img width="540" alt="Screenshot 2023-04-26 160646" src="https://github.com/thebeo2004/Magic-Cat-at-Hogwarts/assets/72870812/2d791af1-03df-4cda-b525-68c86ba7e671">

- Có 2 option: Exit (Tùy chọn 1) và Replay (Tùy chọn 2).

## Nhận xét
- Game vẫn đang thiếu Pause Option.
- Game tự sáng tạo, toàn bộ đều là tự code.

