#include <WiFi.h>
#include <FirebaseESP32.h>

// Thông tin WiFi
const char* ssid = "eoh.io";
const char* password = "Eoh@2020";

// Thông tin Firebase
#define FIREBASE_HOST "your-project-id.firebaseio.com"  // Thay bằng project id của bạn
#define FIREBASE_AUTH "your-auth-token"  // Thay bằng auth token của bạn

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Đang kết nối WiFi...");
  }
  Serial.println("Đã kết nối WiFi!");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Tải ảnh từ camera và lưu lên Firebase
  if (Firebase.set("/images/camera_image.jpg", "image/jpeg", camera_image_data)) {
    Serial.println("Đã lưu ảnh lên Firebase thành công!");
  } else {
    Serial.println("Lỗi khi lưu ảnh lên Firebase:");
    Serial.println(Firebase.errorReason());
  }

  // Dừng sau khi thực hiện một lần
  while (true) {
    delay(1000);
  }
}
