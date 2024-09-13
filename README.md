Viettel Programming Challenge 2024
----------

Đây là lời giải, bình luận và code của cá nhân trong contest hoặc sau contest thông qua suy nghĩ, tìm hiểu và ko phải lời giải chính thức của BTC.

# Bài tập và lời giải

## Đề thi

+ [Đề thi (scan) xem tại đây](dethi/Đề%20thi%20VPC%202024.pdf)


## A. Giao hàng

### Cách làm:
Giả sử tại thời điểm `ti`, xe đang ở `(xi, yi)`, cần di chuyển tới `(x_(i+1), y_(i+1))` vào thời điểm `t_(i+1)`.
Ta nhận thấy thời gian tối thiểu để di chuyển giữa 2 điểm chính là khoảng cách mahattan` d_i = |x_(i+1) - x_i| + |y_(i+1) - y_i|`

- Nếu `d_i <= t_(i+1) - t_i`  có nghĩa xe đủ thời gian để di chuyển tới điểm tiếp theo (đến sớm hơn có thể dừng lại đợi đến `t_(i+1)` để giao hàng).
- Ngược lại `d_i > t_(i+1) - t_i`, thì xe không thể giao kịp đơn hàng tiếp theo.

Do đó ta duyệt, và ở mỗi đơn hàng, ta so sánh 2 giá trị này với nhau để ra kết quả bài toán.

Độ phức tạp: `O(n)`

### Code
[Tham khảo lời giải A](A.cpp) 

## B. Sắp xếp gói tin

### Cách làm:
Giả sử dãy số gốc có index bắt đầu từ 0. 

#### Bước 1.
Nhận thấy số đứng sau số 0, chính là số ở vị trí lẻ đầu tiên của dãy gốc. Nếu tiếp tục lấy số đứng sau số này, sẽ được số ở vị trí lẻ tiếp theo. Tương tự như vậy.

=> Lấy lần lượt dãy các `a_1` (là số đứng sau số 0), `a_2` - số đứng sau số `a_1`, .... tới khi không lấy được tiếp (không còn số đứng sau, hoặc số đứng sau là 0),
=> ta được toàn bộ giá trị ở vị trí *lẻ* của dãy số gốc.

#### Bước 2.
Ta cần điền nốt toàn bộ các giá trị ở vị trí chẵn của dãy gốc.

- TH 1: `n` chẵn
Nhận xét: số ở vị trí chẵn cuối cùng là số đứng trước 0 trong input đầu vào.

=> Lấy dãy `b_1` - là số đừng trước số `0` (b1 chính là số ở vị chẵn cuối cùng của dãy), `b_2` - là số đứng trước `b_1`, ... lấy tới khi không lấy được tiếp.
=> ta được toàn bộ giá trị ở vị trí *chẵn* của dãy số gốc.

- TH 2: `n` lẻ

Giống trường hợp `n` chẵn, tuy nhiên ta cần tìm số cuối cùng ở vị trí chẵn là vị trí nào.
Nhận xét: Số này có đặc điểm không có số nào đứng sau => do vậy ta duyệt tìm xem số này.

=> Duyệt tìm số có đặc điểm này. Sau đó làm tương tự như trường hợp n chẵn.

Như vậy, ta xác định được toàn bộ số ở vị trí chẵn, và vị trí lẻ của dãy gốc => khôi phục được dãy.

Độ phức tạp: `O(n)`

### Code
[Tham khảo lời giải B](B.cpp)

## C. Nhận diện tiếng Việt
*[Too lazy to code]*

## D. Sản xuất điện thoại


Bước 1. Tính số dây chuyền cần thiết xử lý n lô hàng.

Trước khi đếm số dây chuyển nhỏ nhất bằng cách loại bỏ 1 lô hàng, thì ta cần tình số dây chuyền cần thiết để xử lý toàn bộ n lô hàng.

Giả sử n lô hàng cần xử lý trong [l_i, r_i] với `i=1..n`. 

- Xét tập `Head` là tập hợp (unique) tất cả đầu mút `l_i, r_i`. 
- Vỡi mỗi `h` trong `Head`, ta đếm `c[h]` xem có bao nhiêu đơn hàng đang được xử lý (bao gồm đơn hàng vừa bắt đầu, đang xử lý, hoặc kết thúc đúng tại thời điểm đó).
Dễ thấy `max`(`c[h]` với `h` trong `Head`) chính là số dây chuyền cần thiết để xử lý toàn bộ `n` đơn hàng.
Để tính được toàn bộ `c[h]` trong O(n log(n)) ta sử dụng kỹ thuật `sweep line`.

Bước 2. Tính số dây chuyền nhỏ nhất để xử lý n-1 đơn hàng, có thể chọn bất kỳ 1 đơn hàng nào để loại bỏ.

- Giả sử cần `q` dây chuyền để xử lý đơn hàng. Nếu loại bỏ 1 đơn hàng thì số dây chuyền giảm tối đa là 1.
- Ta cần tìm xem có thể loại bỏ lô hàng nào để giảm được 1 dây chuyền.
- Biểu diễn dãy c[h] đã tính ở trên, giả sử vị trí đầu tiên của `q` là `pos_min`, và vị trí cuối cùng là `pos_max`
- Đơn hàng cần loại bỏ phải l_i <= `pos_min`, và `pos_max` <= r_i
thì khi loại bỏ lô hàng này, các phần tử nằm giữa pos_min, pos_max đề giảm đi 1, dãy c[h] sẽ chỉ còn tối đa là `q-1`.
- Nếu không có lô hàng nào như vậy, số dây chuyển nhỏ nhất là `q` (không đổi)

Độ phức tạp: `O(n log(n))`
- O(n log(n)) - cho việc tìm c[h] ở bước 1
- O(n) cho bước 2. 

Tag: sweep line, greedy

### Code
[Tham khảo code](D.cpp)

## E. Mô phỏng tấn công mạng

+ Mỗi bộ định tuyến rìa (edge router) là 1 leaf của tree, ta có thể tính độ trễ của leaf tới root bằng dfs + dp.
Tới đây, ta biết được danh sách các leaf, độ trễ từ leaf tới root.
+ Ta cần trả lời q query: xoá 1 node trên cây, và trả về độ trễ nhỏ nhất trong các leaf còn lại có kết nối tới root.

Có 2 cách tiếp cận:
### Cách 1: 
  - Lưu toàn bộ độ trễ d[l] của các leaf vào multiset (nhiều leaf có thể có d[l] giống nhau).
  - Mỗi lần cắt node v khỏi tree, ta cần xoá toàn bộ leaf thuộc subtree của v. Để làm việc này, ta dfs từ v.
  - Để trả lời câu hỏi độ trễ nhỏ nhất ta lấy min của multiset.

Độ phức tạp: `O(n log(n))`: 
- Do mỗi cạnh chỉ được duyệt 1 lần khi xoá đỉnh v => `O(n)` cho toàn bộ việc xoá cạnh cho tất cả query.
- Xoá 1 phần tử khỏi multiset trong `log(n)` => `O(n log(n))` cho toàn bộ việc xoá phần tử
- Trả lời câu hỏi min của multiset trong `O(1)`

### Cách 2:
  - Xét các leaf được duyệt theo thứ tự visit của dfs, giả sử có k leaf, gọi d là dãy độ trễ từ leaf tới root. Ta có dãy `d[0], d[1], d[2], .... d[k-1]`.
  - Khi hỏi độ trễ nhỏ nhất của leaf, tương đương tìm min của dãy `d` kể trên.
  - Mỗi node v sẽ là cha của một số leaf liên tiếp trong dãy trên. Để biết node v quản lý những leaf nào, ta lưu thêm thông tin mỗi node quản lý từ leaf nào tới leaf nào trên cây.
  - Kí hiệu node v quản lý các node từ [l_v, r_v]
  - Khi xoá node v khỏi cây, tương đương Update toàn bộ d[i] với l_v <= i <= r_v với 1 giá trị `INF` (INF đủ lớn để khi tìm min của dãy) 
  - Thực hiện tìm min của d.

Bài toán được đưa về bài toán: Cho 1 dãy số, có 2 loại truy vấn:
- update toàn bộ range của 1 dãy
- trả lời min của 1 range (bài toàn này luôn lấy min của range cố định [0, k-1]).

=> bài toán này giải quyết bằng cấu trúc dữ liệu Segment Tree, cùng kỹ thuật lazy propagation. Tham khảo thêm ở [đây](https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation)

Độ phức tạp: `O(n log(n))`

Tag: dp, dfs or segment tree

### Code
- [Code sử dụng dp, dfs đơn thuần (dễ triển khai)](E2.cpp)
- [Code sử dụng segment tree + lazy propagation: khó code, nhưng giải được nhiều bài hơn](E.cpp)

## F. Kiểm soát truy cập

Biến đổi biểu diễn CIDR dạng `x1.x2.x3.x4` hoặc `x1.x2.x3.x4/n`
thành 2 thông tin: 
- `state`: dạng số của `x1.x2.x3.x4` ở trên, cụ thể `state = x1 * 256^3 + x2 * 256^2 + x3 * 256 + x4` 
- `bit`: là số bit được fixed trong biểu diễn, chính là `n` ở trên, hoặc = `32` (tương đương fix toàn bộ 32 bit - 1 ip cố định)

Ví dụ:
- 192.168.1.2 => state = 3,232,235,778, bit = 32
- 192.168.1.0/24 => state = 3,232,235,776, bit = 24
 
Xét 1 cây nhị phân Trie, 32 levels, mỗi node có 2 children.
Mỗi node biểu diễn 1 chuỗi bit. Trong đó
- Root = ''
- Node.leftChild = Node + '0'; (node con bên trái sẽ append thêm bit 0)
- Node.rightChild = Node + '1'; (node con bên phải sẽ append thêm bit 1)

Như vậy mỗi IP cố định sẽ tương đương 1 lá (ở level 32) của cây. MỖi dải IP fix n bit (x1.x2.x3.x4/n) sẽ tương đương 1 node ở level n của cây.

Trên mỗi node này, ta sẽ lưu thêm thông tin: tại node này, có thông tin Accept hay Deny không, và nếu có thì lệnh này có thứ tự bao nhiêu trong tập lệnh (phục vụ so sánh về mức độ ưu tiên khi so sánh sau này).

Giả sử có lệnh ở dòng thứ 1000 có lệnh `A 192.168.1.2` => thì trên cây Trie, tại state `3,232,235,778` khi biểu diễn trên cây Trie sẽ có thông tin Accept, với thông tin thứ tự = 1000. 

=> Khi nhận các update dạng A/D IP/n thì ta chỉ việc quy đổi (state, bit) và traverse tới node có state tương ứng ở level `bit` trên cây, và update thông tin (Accept/Deny) cũng như thứ tự của lệnh.

- Để trả lời câu hỏi: 1 ip có được truy cập không thì ta duyệt từ root -> leaf của state tương ứng ip này, khi gặp 1 node có thông tin về accept/deny thì cập nhật thông tin: thứ tự nhỏ nhất của lệnh accept, thứ tự nhỏ nhất của lệnh deny.
- So sánh 2 giá trị này với nhau để ra được ip đó accept/deny.


Tag: Trie

### Code
[Tham khảo lời giải](F.cpp)


## G. Quan trắc không gian
Phân tích:
Giả sử k là số hành tinh chung lớn nhất được quan sát cả 2 lần. Thì số lượng hành tinh nhỏ nhất được quan sát là `n+m-k` (vì có k hành tinh bị quan sát lặp).
Do vậy bài toán tương đương tìm số k hành tinh chung lớn nhất quan sát được ở cả 2 lần.

Bài toán tương đương, tìm `k` lớn nhất để tồn tại `k` số `{a_i1, a_i2, ... a_ik}` thuộc `A` và `k` số `{b_j1, b_j2, ..., b_jk}` thuộc `B`,
thoả mãn `a_i1/b_j1 = a_i2/b_j2 = ... = a_ik/b_jk`.

#### Trường hợp đơn giản: A gồm toàn phần tử phân biệt, B cũng thế.
 
Xét n*m cặp `(i, j) = a_i / b_j` trong đó `a_i in A, b_j in B`.

Ta quy `a_i / b_j` thành giá trị, dễ thấy giá trị x nào đó xuất hiện nhiều lần nhất, thì đây chính là số k cần tìm.

Tuy nhiên với giá trị double thì xử lý có thể có sai số, do vậy ta chuyển a_i/b_j thành dạng normal form để giá trị giống nhau thì biểu diễn như nhau.
1 cách biểu diễn là với a/b thì ta biểu diễn thành `a'/b'` với `a' = a/UCLN(a,b), b' = b / UCLN(a,b)`, trong đó UCLN(a,b) là ước chung lớn nhất của a,b.
Ví dụ: `9/18 -> 1/2, 2/4 -> 1/2`.

=> Từ đó ta duyệt trong `n*m` cặp, biến đổi `a_i / b_j` thành dạng normal form, dùng map để đếm số lần xuất hiện. value lớn nhất của map chính là số k.


#### Trường hợp còn lại: A, B có những giá trị lặp lại.
Lúc này ta quy về trường hợp 1, tuy nhiên với mỗi a lặp fa lần trong A, b lặp fb lần trong B, khi ghép cặp thì thay vì chỉ được 1 cặp ta sẽ được min(fa, fb) cặp.

Tag: Math

### Code
[Tham khảo](G.cpp)

## H. Trò chơi bốc sỏi
Tag: Classical Nim

Bài toán NIM gốc là:
Có n đống sỏi, mỗi đống có 1 số lượng sỏi a1 -> an. 2 người chơi lần lượt bốc 1 số > 0 viên sỏi ở 1 đống bất kỳ còn sỏi.
Đến lượt, người nào không chơi được là thua.
2 người đều chơi tối ưu, hỏi người đi trước thắng hay thua.

Đáp án bài này là: 
Xét `state = a1 xor a2 xor a3 ... xor an`
(XOR là phép toán xor bit, trong đó 0 xor 1 = 1, 1 xor 1 = 0 xor 0 = 0)

Nếu `state = 0` => người đầu luôn thua, `nim != 0` => người đầu luôn thắng.

Bài H này, khác ở 2 điểm:
(1) Mỗi lượt chơi người chơi phải bốc số lượng sỏi giống nhau, ở số lượng lẻ cột (1,3,5 cột)
(2) Thay vì trả lời trạng thái hiện tại là thắng / thua thì đề bài đảm bảo người đầu luôn thắng, nhưng cần in ra tất cả cách khác nhau về nước đi đầu tiên.

Điểm (1) tuy có khác, nhưng bản chất nếu state = a1 xor a2 ... xor a5 != 0 thì người đầu luôn thắng
(Có thể chứng minh bằng lý thuyết và có thể thử tất cả trường hợp bằng code để kiểm chứng (Tham khảo [code thử](H_Analyze.cpp)))

Như vậy, từ trạng thái ban đầu gồm (a1, a2, a3, a4, a5), ta cần các cách khác nhau, bao gồm:
- tìm số lẻ cọc liền nhau (1 cọc, 3 cọc, 5 cọc).
- số x <= các cọc được chọn và state_x = (a-x) XOR (b-x) ... = 0


## I. 4G-Data
TODO:

## J. BST1
Tag: Combinatorics

Bài này mấu chốt phải nhận ra: k^2 = số cách chọn 2 điểm (i, j) trong thành phần liên thông có k đỉnh.
Từ đó decomposition k^2 thành các pair...

### Code 
[Tham khảo](J.cpp)

## K. BTS2

Tag: Fast Fourier Transform

TODO:

## L. Chip
TODO:


# Nhận xét
