//
//  ProfileView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct ProfileView: View {
    @State private var showingEditProfileScreen = false
    @State var avatar: Image?
    
    @AppStorage("username") var username = "username"
    @AppStorage("firstname") var firstname = "Name"
    @AppStorage("lastname") var lastname = "Surname"
    @State var birthday = Date()
//    @AppStorage("birthday", store: ) var birthday = Data()
    @AppStorage("email") var email = "Email"
    @AppStorage("phoneNumber") var phoneNumber = "Phone Number"
    @AppStorage("visitedCountry") var visitedCountry = "0 (visited country)"
    
    var body: some View {
        NavigationView {
            VStack {
                VStack {
                    Image("profile-ava")
                        .resizable()
                        .frame(width: 120, height: 120)
                        .clipShape(Circle())
                    
                    Text(username)
                        .font(.title)
                        .bold()
                }
                
                Spacer()
                    .frame(height: 30)
                
                VStack(alignment: .leading, spacing: 12) {
                    HStack {
                        Image(systemName: "info.circle")
                        Text(firstname + " " + lastname)
                    }
                    
                    HStack {
                        Image(systemName: "birthday.cake")
                        Text(birthday.formatted())
                    }
                    
                    HStack {
                        Image(systemName: "envelope")
                        Text(email)
                    }
                    
                    HStack {
                        Image(systemName: "phone")
                        Text(phoneNumber)
                    }
                    
                    HStack {
                        Image(systemName: "checkmark.circle.fill")
                        Text(visitedCountry)
                    }
                }
                
                Spacer()
                    .frame(height: 30)
                
                Button {
                    showingEditProfileScreen.toggle()
                } label: {
                    Text("Update Profile")
                        .bold()
                        .frame(width: 260, height: 50)
                        .background(Color.red)
                        .foregroundColor(.white)
                        .cornerRadius(12)
                }
            }
            .navigationTitle("Account")
            .navigationBarTitleDisplayMode(.inline)
        }
        .sheet(isPresented: $showingEditProfileScreen) {
            EditProfileView(
                image: $avatar,
                username: $username,
                firstname: $firstname,
                lastname: $lastname,
                birthday: $birthday,
                email: $email,
                phoneNumber: $phoneNumber
            )
        }
    }
}

struct ProfileView_Previews: PreviewProvider {
    static var previews: some View {
        ProfileView()
            .preferredColorScheme(.light)
        ProfileView()
            .preferredColorScheme(.dark)
    }
}
