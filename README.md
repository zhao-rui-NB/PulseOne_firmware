# PulseOne_firmware

# PulseOne BLE 系統讀寫格式說明文檔

## 服務概述

PulseOne 設備提供四個主要 BLE 服務，每個服務包含不同的特徵值，用於不同的功能區域。

| 服務名稱 | UUID | 描述 |
|---------|------|------|
| System State | d94c1000-58fe-4099-bc79-39a21e540e89 | 系統狀態相關信息 |
| User List | d94c2000-58fe-4099-bc79-39a21e540e89 | 用戶管理與設置 |
| Monitor | d94c3000-58fe-4099-bc79-39a21e540e89 | 健康監測數據 |
| Inject | d94c4000-58fe-4099-bc79-39a21e540e89 | 注射相關信息 |

## System State 服務

系統狀態服務包含當前系統頁面和登錄用戶信息。

| 特徵值 | UUID | 屬性 | 格式 | 描述 |
|-------|------|------|------|------|
| 頁面 | d94c1001-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 當前顯示的頁面名稱 |
| 登錄用戶 | d94c1002-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 當前登錄的用戶信息 |

## User List 服務

用戶列表服務用於管理和設置用戶信息。

| 特徵值 | UUID | 屬性 | 格式 | 描述 |
|-------|------|------|------|------|
| 用戶 ID | d94c2001-58fe-4099-bc79-39a21e540e89 | 讀取, 寫入 | 字符串 | 當前選擇的用戶 ID，範圍 "0"-"7" |
| 用戶有效性 | d94c2002-58fe-4099-bc79-39a21e540e89 | 讀取, 寫入 | 字符串 | 用戶數據是否有效："0"=無效，"1"=有效 |
| 用戶名稱 | d94c2003-58fe-4099-bc79-39a21e540e89 | 讀取, 寫入 | 字符串 | 用戶名稱，最大長度 19 字符 |
| 用戶頭像 ID | d94c2e04-58fe-4099-bc79-39a21e540e89 | 讀取, 寫入 | 字符串 | 用戶頭像 ID，範圍 "0"-"2" |

## Monitor 服務

健康監測服務提供各種生理指標的數據。

| 特徵值 | UUID | 屬性 | 格式 | 描述 |
|-------|------|------|------|------|
| 心率 | d94c3001-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 心率數據（如 "72"） |
| 血氧飽和度 | d94c3002-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 血氧飽和度數據（如 "98"） |
| 血糖 | d94c3003-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 血糖數據（如 "5.6"） |
| 收縮壓 | d94c3004-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 血壓收縮壓數據（如 "120"） |
| 舒張壓 | d94c3005-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 血壓舒張壓數據（如 "80"） |

## Inject 服務

注射服務提供胰島素和碳水化合物攝入的信息。

| 特徵值 | UUID | 屬性 | 格式 | 描述 |
|-------|------|------|------|------|
| 胰島素 | d94c4001-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 胰島素注射數據（如 "4.5"） |
| 碳水化合物 | d94c4002-58fe-4099-bc79-39a21e540e89 | 讀取, 通知 | 字符串 | 碳水化合物攝入數據（如 "45"） |

## 操作說明

### 數據格式說明

**重要：所有數據均以字符串形式傳輸，即使是數值型數據。**

例如：
- 用戶 ID 為 0 時，傳輸的是字符串 "0"
- 血糖值為 5.6 時，傳輸的是字符串 "5.6"
- 用戶有效狀態為「有效」時，傳輸的是字符串 "1"

### 讀取和寫入機制

1. **讀取操作**
   - 對於帶有讀取屬性的特徵值，客戶端可以直接讀取當前值
   - 讀取時會返回對應的字符串

2. **寫入操作**
   - 對於帶有寫入屬性的特徵值，客戶端可以發送新的字符串值
   - 例如設置用戶 ID 為 2，需寫入字符串 "2"
   - 寫入數字類型時，需轉換為字符串後再傳輸

3. **通知機制**
   - 對於帶有通知屬性的特徵值，客戶端可以註冊接收通知
   - 當特徵值更新時，設備會自動推送新的字符串值給已註冊的客戶端

### 用戶管理流程

1. 寫入用戶 ID（字符串 "0" 到 "7"）選擇要操作的用戶
2. 讀取或寫入該用戶的各項屬性（有效性、名稱、頭像等）
3. 如需創建新用戶，先選擇未使用的 ID，設置用戶名稱和頭像，最後將有效性設為 "1"


### 注意事項

- 所有數值都作為字符串傳輸，應用程序需要自行轉換
- 用戶名稱最大長度為 19 字符，超出部分會被自動截斷
- 用戶頭像 ID 範圍為 "0"-"2"，對應系統預設的三種頭像
- 健康數據（心率、血氧等）僅支持讀取和通知，不支持直接寫入
