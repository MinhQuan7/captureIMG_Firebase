import requests
import firebase_admin
from firebase_admin import credentials, storage

# Khởi tạo Firebase Admin SDK
cred = credentials.Certificate("F:/EoH Company/Capture_Image_iFrame/firebase/codeCaptureIMG_Camera/captureimage-38a12-firebase-adminsdk-ngvh0-880c1349a3.json")
firebase_admin.initialize_app(cred, {
    'storageBucket': 'captureimage-38a12.appspot.com'  #projectID
})

def capture_and_upload_image():
    # Tải ảnh từ HIKVISION
    url = "http://admin:Eoh54321@14.241.233.207:28001/ISAPI/Streaming/channels/1/picture"
    response = requests.get(url)

    if response.status_code == 200:
        # Tải ảnh lên Firebase Storage
        bucket = storage.bucket()
        blob = bucket.blob('images/camera_image.jpg')
        blob.upload_from_string(response.content, content_type='image/jpeg')
        
        # Tạo URL công khai
        blob.make_public()
        print('Public URL:', blob.public_url)
        
        return blob.public_url
    else:
        print("Lỗi khi tải ảnh từ camera:", response.status_code)
        return None

#
public_url = capture_and_upload_image()

if public_url:
    print("URL công khai của ảnh:", public_url)
