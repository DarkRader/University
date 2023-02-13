//
//  EditProfileView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct EditProfileView: View {
    @Binding var image: Image?
    @State var isImagePickerPres = false
    @State var decodedString = ""
    @Environment(\.dismiss) var dismiss
    
    @Binding var username: String
    @Binding var firstname: String
    @Binding var lastname: String
    @Binding var email: String
    @Binding var phoneNumber: String
    
    var body: some View {
        NavigationView {
            Form {
                Section("Avatar") {
                    Circle()
                        .fill(.gray)
                        .frame(width: 150, height: 150)
                        .aspectRatio(1, contentMode: .fit)
                        .padding(.horizontal, 70)
                        
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
                                decodedString: $decodedString
                            )
                        }
                }
                Section("Username") {
                    TextEditor(text: $username)
                }

                Section("First Name") {
                    TextEditor(text: $firstname)
                }
                Section("Last Name") {
                    TextEditor(text: $lastname)
                }
                Section("Email") {
                    TextEditor(text: $email)
                }
                Section("Phone Number") {
                    TextEditor(text: $phoneNumber)
                }
            }
            .navigationTitle("Account Edit")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("Save") {
                        Task {
//                            await addPost(description: description, decodedString: decodedString)
                        }
                       dismiss()
                    }
                }
            }
        }
    }
    
}

struct EditProfileView_Previews: PreviewProvider {
    
    @State static var image: Image?
    @State static var username = ""
    @State static var firstname =  ""
    @State static var lastname = ""
    @State static var email = ""
    @State static var phoneNumber = ""
    
    static var previews: some View {
        EditProfileView(
            image: $image,
            username: $username,
            firstname: $firstname,
            lastname: $lastname,
            email: $email,
            phoneNumber: $phoneNumber
        )
    }
}
    
    struct ImagePickers: UIViewControllerRepresentable {
        @Binding var image: Image?
        @Binding var isPresented: Bool
        @Binding var decodedString: String
        
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
                print(self.decodedString)
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
