#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9
#define TOTAL_CELLS 81

// ==================== CẤU TRÚC DỮ LIỆU ====================

// Tọa độ của một ô (x: hàng, y: cột, giá trị từ 0-8)
typedef struct {
    int x;
    int y;
} Coord;

// Danh sách tọa độ - lưu các ô liên quan
typedef struct {
    Coord data[TOTAL_CELLS];
    int size;
} ListCoord;

// Ma trận ràng buộc (đỉnh-đỉnh) cho 81 ô
typedef struct {
    int data[TOTAL_CELLS][TOTAL_CELLS];
} Constrains;

// Cấu trúc bảng Sudoku
typedef struct {
    int cells[N][N];        // Ma trận 9x9 chứa giá trị các ô
    Constrains constrains;  // Ràng buộc giữa các ô
} Sudoku;

// ==================== HÀM CHUYỂN ĐỔI TỌA ĐỘ ====================

// Chuyển từ tọa độ (x, y) sang chỉ số đỉnh (0-80)
int indexOf(Coord coord) {
    return coord.x * N + coord.y;
}

// Chuyển từ chỉ số đỉnh (0-80) sang tọa độ (x, y)
Coord positionOfVertex(int vertex) {
    Coord coord;
    coord.x = vertex / N;
    coord.y = vertex % N;
    return coord;
}

// ==================== HÀM XỬ LÝ RÀNG BUỘC ====================

// Khởi tạo ràng buộc rỗng (tất cả = 0)
void initConstrains(Constrains *cons) {
    for (int i = 0; i < TOTAL_CELLS; i++) {
        for (int j = 0; j < TOTAL_CELLS; j++) {
            cons->data[i][j] = 0;
        }
    }
}

// Thêm ràng buộc giữa 2 ô (ô u và ô v không được có cùng giá trị)
void addConstrain(Constrains *cons, Coord coord1, Coord coord2) {
    int u = indexOf(coord1);
    int v = indexOf(coord2);
    if (u != v) {  // Không thêm ràng buộc với chính nó
        cons->data[u][v] = 1;
        cons->data[v][u] = 1;
    }
}

// Lấy danh sách tất cả các ô có ràng buộc với ô cho trước
ListCoord getConstrains(Constrains *cons, Coord coord) {
    ListCoord list;
    list.size = 0;
    int u = indexOf(coord);
    
    for (int v = 0; v < TOTAL_CELLS; v++) {
        if (cons->data[u][v] == 1) {
            list.data[list.size] = positionOfVertex(v);
            list.size++;
        }
    }
    return list;
}

// Thiết lập tất cả ràng buộc cho bảng Sudoku
void setupAllConstrains(Constrains *cons) {
    initConstrains(cons);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Coord current = {i, j};
            
            // Ràng buộc HÀNG: các ô cùng hàng i
            for (int col = 0; col < N; col++) {
                if (col != j) {
                    Coord other = {i, col};
                    addConstrain(cons, current, other);
                }
            }
            
            // Ràng buộc CỘT: các ô cùng cột j
            for (int row = 0; row < N; row++) {
                if (row != i) {
                    Coord other = {row, j};
                    addConstrain(cons, current, other);
                }
            }
            
            // Ràng buộc KHỐI 3x3
            int blockRowStart = (i / 3) * 3;
            int blockColStart = (j / 3) * 3;
            for (int r = blockRowStart; r < blockRowStart + 3; r++) {
                for (int c = blockColStart; c < blockColStart + 3; c++) {
                    if (r != i || c != j) {
                        Coord other = {r, c};
                        addConstrain(cons, current, other);
                    }
                }
            }
        }
    }
}

// ==================== HÀM THAO TÁC BẢNG SUDOKU ====================

// Khởi tạo bảng Sudoku rỗng (tất cả ô = 0)
void initSudoku(Sudoku *sudoku) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sudoku->cells[i][j] = 0;
        }
    }
    setupAllConstrains(&sudoku->constrains);
}

// Khởi tạo bảng Sudoku từ dữ liệu đầu vào
void initSudokuWithValues(Sudoku *sudoku, int values[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sudoku->cells[i][j] = values[i][j];
        }
    }
    setupAllConstrains(&sudoku->constrains);
}

// In bảng Sudoku ra màn hình
void printSudoku(Sudoku *sudoku) {
    printf("\n+-------+-------+-------+\n");
    for (int i = 0; i < N; i++) {
        printf("| ");
        for (int j = 0; j < N; j++) {
            if (sudoku->cells[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", sudoku->cells[i][j]);
            }
            if ((j + 1) % 3 == 0) {
                printf("| ");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
    }
}

// Kiểm tra giá trị có hợp lệ tại vị trí (row, col) không
int isValidValue(Sudoku *sudoku, int row, int col, int value) {
    Coord coord = {row, col};
    ListCoord neighbors = getConstrains(&sudoku->constrains, coord);
    
    for (int i = 0; i < neighbors.size; i++) {
        int nx = neighbors.data[i].x;
        int ny = neighbors.data[i].y;
        if (sudoku->cells[nx][ny] == value) {
            return 0;  // Vi phạm ràng buộc
        }
    }
    return 1;  // Hợp lệ
}

// Kiểm tra bảng đã được điền đầy đủ và thỏa mãn ràng buộc chưa
int isFilledSudoku(Sudoku *sudoku) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Kiểm tra ô trống
            if (sudoku->cells[i][j] == 0) {
                return 0;
            }
            // Kiểm tra giá trị hợp lệ (1-9)
            if (sudoku->cells[i][j] < 1 || sudoku->cells[i][j] > 9) {
                return 0;
            }
        }
    }
    
    // Kiểm tra tất cả ràng buộc
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Coord coord = {i, j};
            ListCoord neighbors = getConstrains(&sudoku->constrains, coord);
            int value = sudoku->cells[i][j];
            
            for (int k = 0; k < neighbors.size; k++) {
                int nx = neighbors.data[k].x;
                int ny = neighbors.data[k].y;
                if (sudoku->cells[nx][ny] == value) {
                    return 0;  // Vi phạm ràng buộc
                }
            }
        }
    }
    return 1;  // Bảng hợp lệ và đã điền đầy đủ
}

// ==================== GIẢI SUDOKU BẰNG BACKTRACKING + CSP ====================

// Tìm ô trống tiếp theo (trả về 1 nếu tìm thấy, 0 nếu không)
int findEmptyCell(Sudoku *sudoku, int *row, int *col) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sudoku->cells[i][j] == 0) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

// Giải Sudoku bằng Backtracking với Constraint Propagation
int solveSudoku(Sudoku *sudoku) {
    int row, col;
    
    // Nếu không còn ô trống -> đã giải xong
    if (!findEmptyCell(sudoku, &row, &col)) {
        return 1;
    }
    
    // Thử các giá trị từ 1 đến 9
    for (int num = 1; num <= 9; num++) {
        if (isValidValue(sudoku, row, col, num)) {
            // Gán giá trị
            sudoku->cells[row][col] = num;
            
            // Đệ quy giải tiếp
            if (solveSudoku(sudoku)) {
                return 1;
            }
            
            // Backtrack: hoàn tác nếu không tìm được lời giải
            sudoku->cells[row][col] = 0;
        }
    }
    
    return 0;  // Không có lời giải
}

// ==================== CHƯƠNG TRÌNH CHÍNH ====================

int main() {
    Sudoku sudoku;
    
    // Bảng Sudoku mẫu (0 = ô trống)
    int puzzle[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    // Khởi tạo bảng Sudoku
    initSudokuWithValues(&sudoku, puzzle);
    
    printf("=== BAI TOAN SUDOKU - CSP ===\n");
    printf("\nBang Sudoku ban dau:");
    printSudoku(&sudoku);
    
    printf("\nDang giai bang Constraint Satisfaction Problem...\n");
    
    // Giải Sudoku
    if (solveSudoku(&sudoku)) {
        printf("\nLoi giai tim duoc:");
        printSudoku(&sudoku);
        
        // Kiểm tra kết quả
        if (isFilledSudoku(&sudoku)) {
            printf("\n[OK] Bang Sudoku da duoc dien day du va thoa man tat ca rang buoc!\n");
        }
    } else {
        printf("\nKhong tim duoc loi giai cho bang Sudoku nay!\n");
    }
    
    // Demo: Hiển thị các ô có ràng buộc với ô (0,0)
    printf("\n--- Demo: Cac o co rang buoc voi o (0,0) ---\n");
    Coord testCoord = {0, 0};
    ListCoord neighbors = getConstrains(&sudoku.constrains, testCoord);
    printf("So o co rang buoc: %d\n", neighbors.size);
    printf("Danh sach: ");
    for (int i = 0; i < neighbors.size; i++) {
        printf("(%d,%d) ", neighbors.data[i].x, neighbors.data[i].y);
    }
    printf("\n");
    
    return 0;
}