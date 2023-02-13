//
//  AddPostView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 13.02.2023.
//

import SwiftUI

struct AddPostView: View {
    
    @AppStorage("profileImageData") private var profileImageData: Data?
    @AppStorage("username") var username = "username"
    
    @State private var image = ""
    @State private var description = ""
    @State private var city = ""
    @State private var country = ""
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    var body: some View {
        NavigationView {
            Form {
                Section("Information about user") {
                    VStack(alignment: .leading) {
                        HStack {
                            if let data = profileImageData, let image = UIImage(data: data) {
                               Image(uiImage: image)
                                    .resizable()
                                    .scaledToFill()
                                    .clipShape(Circle())
                                    .frame(width: 36, height: 36)
                           } else {
                               Image("profile-ava")
                                   .resizable()
                                   .scaledToFill()
                                   .clipShape(Circle())
                                   .frame(width: 36, height: 36)
                           }
                            
                            Text(username)
                        }
                    }
                }
                
                Section("Write city and country") {
                    TextField("City", text: $city)
                    TextField("Country", text: $country)
                }
                
                Section("Add image (copy URL your image)") {
                    TextEditor(text: $image)
                }
                
                Section("My description") {
                    TextEditor(text: $description)
                        .font(.system(.body))
                        .frame(height: max(100,20))
                        .cornerRadius(10.0)
                        .shadow(radius: 1.0)
                }
                
                Section {
                    Button("Save") {
                        // Add a new post
                        let post = CoreDataPost(context: moc)
                        post.id = UUID().uuidString
                        post.photo = image
                        post.country = country
                        post.city = city
                        post.descrip = description
                        post.likes = 0
                        post.comments = 0
                        
                        do {
                            try moc.save()
                        } catch {
                            print("ERROR SAVING TO CORE DATA:", error.localizedDescription)
                        }
                        
                        dismiss()
                    }
                }
                
            }
        }
        .navigationTitle("Add post")
    }
    
    private func saveToFileSystem(posts: [Post]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PostSave.url)
        let data = try? JSONEncoder().encode(posts)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("POSTS SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(posts: [Post]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(posts),
            forKey: PostSave.userDefaultsKey
        )
    }
}

struct AddPostView_Previews: PreviewProvider {
    static var previews: some View {
        AddPostView()
    }
}
