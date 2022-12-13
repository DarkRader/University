//
//  TestAddNewPostView.swift
//  Fitstagram
//
//  Created by DarkRader on 12.12.2022.
//

import SwiftUI

struct AddPostRequest: Encodable {
    let text: String
    let photos: [String]
}

struct ResponseFailure: Decodable {
    let message: String
}
struct ResponseSuccess: Decodable {
    let id: String
}

struct AddNewPostView: View {
    @State var posts: [Post] = []
    @Environment(\.dismiss) var dismiss
    
    @State var image: Image?
    @State var isImagePickerPres = false
    @State var decodedString = ""
    @State var description = ""
    
    var body: some View {
        NavigationView {
            Form {
                Section("Add photo") {
                    Rectangle()
                        .fill(.gray)
                        .aspectRatio(1, contentMode: .fit)
                        .overlay {
                            if let image {
                                image
                                    .resizable()
                                    .aspectRatio(contentMode: .fill)
                            }
                        }
                        .clipped()
                        .overlay(
                            Button {
                                isImagePickerPres = true
                            } label: {
                                Circle()
                                    .fill(.white)
                                    .frame(width: 64, height: 64)
                                    .overlay(
                                        Image(systemName: "plus")
                                            .resizable()
                                            .padding()
                                    )
                            }
                        )
                        .fullScreenCover(isPresented: $isImagePickerPres) {
                            ImagePickers(
                                image: $image,
                                isPresented: $isImagePickerPres,
                                decodedString: $decodedString,
                                description: $description
                            )
                        }
                }
                
                Section("Add description") {
                    TextEditor(text: $description)
                        .font(.system(.body))
                        .frame(height: max(100,20))
                        .cornerRadius(10.0)
                        .shadow(radius: 1.0)
                }
                
                
                Section {
                    Button("Save") {
                        Task {
                            await addPost(description: description, decodedString: decodedString)
                        }
                       dismiss()
                    }
                    
                }
            }
        }
        .navigationTitle("Add Post")
    }
    
}

func addPost(description: String, decodedString: String) async {//async {

        guard !decodedString.isEmpty else { return }

        let url = URL(string: "https://fitstagram.ackee.cz/api/feed")!

        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.setValue("kuznear1", forHTTPHeaderField: "Authorization")

        let body = AddPostRequest(text: description, photos: [decodedString])
        let json = try! JSONEncoder().encode(body)
        let httpBody = String(data: json, encoding: .utf8)!
        request.httpBody = httpBody.data(using: .utf8)
    
        do {
            let (_, response) = try await URLSession.shared.data(for: request)
            print(response)

        } catch {
            print("[ERROR]", error.localizedDescription)
        }
    
    }

struct TestAddNewPostView_Previews: PreviewProvider {
    static var previews: some View {
        AddNewPostView()
    }
}

struct ImagePickers: UIViewControllerRepresentable {
    @Binding var image: Image?
    @Binding var isPresented: Bool
    @Binding var decodedString: String
    @Binding var description: String

    func makeUIViewController(context: Context) -> UIImagePickerController {
        let controller = UIImagePickerController()
        controller.delegate = context.coordinator
        return controller
    }

    func updateUIViewController(
        _ uiViewController: UIImagePickerController,
        context: Context
    ) { }

    func makeCoordinator() -> Coordinator {
        Coordinator(image: $image, isPresented: $isPresented, decodedString: $decodedString)
    }

    final class Coordinator: NSObject, UINavigationControllerDelegate, UIImagePickerControllerDelegate {
        @Binding var image: Image?
        @Binding var isPresented: Bool
        @Binding var decodedString: String

        init(image: Binding<Image?>, isPresented: Binding<Bool>, decodedString: Binding<String>) {
            self._image = image
            self._isPresented = isPresented
            self._decodedString = decodedString
        }

        func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
            isPresented = false
        }

        func imagePickerController(
            _ picker: UIImagePickerController,
            didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]
        ) {
            guard let image = info[.originalImage] as? UIImage else { return }
            self.image = Image(uiImage: image)
            let newImage = resizeImage(image: image, targetSize: CGSize(width: 1000, height: 1000))
            self.isPresented = false
            self.decodedString = convertImageToBase64String(img: (newImage)!)
        }
        
        func resizeImage(image: UIImage, targetSize: CGSize) -> UIImage? {
            let size = image.size
            
            let widthRatio  = targetSize.width  / size.width
            let heightRatio = targetSize.height / size.height

            var newSize: CGSize
            if(widthRatio > heightRatio) {
                newSize = CGSize(width: size.width * heightRatio, height: size.height * heightRatio)
            } else {
                newSize = CGSize(width: size.width * widthRatio, height: size.height * widthRatio)
            }
            
            let rect = CGRect(origin: .zero, size: newSize)
            
            UIGraphicsBeginImageContextWithOptions(newSize, false, 1.0)
            image.draw(in: rect)
            let newImage = UIGraphicsGetImageFromCurrentImageContext()
            UIGraphicsEndImageContext()
            
            return newImage
        }
        
        func convertImageToBase64String(img: UIImage) -> String {
            return img.jpegData(compressionQuality: 1)?.base64EncodedString() ?? ""
        }
    }


}
