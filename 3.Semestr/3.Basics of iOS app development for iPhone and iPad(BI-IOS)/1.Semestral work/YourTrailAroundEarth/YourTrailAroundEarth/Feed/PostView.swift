//
//  PostView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 13.02.2023.
//

import SwiftUI

struct PostView: View {
    @State private var mapAPI = MapAPI()
    
    @State private var showMap = false
    
    @AppStorage("profileImageData") private var profileImageData: Data?
    @AppStorage("username") var username = "username"
    
    private var post: CoreDataPost
    
    init(post: CoreDataPost) {
        self.post = post
    }
    
    var body: some View {
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

                VStack(alignment: .leading) {
                    Text(username)
                        .font(.callout)
                        .fontWeight(.semibold)
                    
                    HStack {
                        Text("\(post.city ?? ""),")
                        Text(post.country ?? "")
                    }
                    .font(.system(size: 12))
                }
                
                Spacer()
                
                Button(action: { }) {
                    Image(systemName: "ellipsis")
                }
            }
            .padding(.horizontal, 8)
          
            RemoteImage(url: URL(string: post.photo ?? "")!)
                .frame(width: 360, height: 300)
            
            HStack(spacing: 16) {
                HStack(spacing: 4) {
                    Button(action: { }) {
                        Image(systemName: "heart")
                    }
                    Text("\(post.likes)")
                        .foregroundColor(Color.blue)
                }
                
                HStack(spacing: 4) {
                    Button(action: { }) {
                        Image(systemName: "message")
                    }
                    Text("\(post.comments)")
                        .foregroundColor(Color.blue)
                }
                
                Button(action: { }) {
                    Image(systemName: "paperplane")
                }
                
                Spacer()
                
                HStack {
                    Button(action: {
                        mapAPI.getLocation(address: post.city ?? "", delta: 1)
                    }) {
                        Image(systemName: "location")
                    }
                    .buttonStyle(BorderlessButtonStyle())
                    
                    Button(action: {
                        showMap.toggle()
                    }) {
                        Image(systemName: "mappin.and.ellipse")
                    }
                    .buttonStyle(BorderlessButtonStyle())
                }
            }
            .padding(.horizontal, 8)
            .padding(.vertical, 2)
            
//            HStack {
//                Button(action: {
//                    mapAPI.getLocation(address: post.city ?? "", delta: 1)
//                }) {
//                    Image(systemName: "location")
//                }
//                .buttonStyle(BorderlessButtonStyle())
//
//                Button(action: {
//                    showMap.toggle()
//                }) {
//                    Image(systemName: "mappin.and.ellipse")
//                }
//                .buttonStyle(BorderlessButtonStyle())
//            }
            
            Group {
                Text(username)
                    .fontWeight(.semibold)
                +
                Text(": \(post.descrip ?? "")")
            }
            .padding(.horizontal, 8)
            
        }
        .sheet(isPresented: $showMap) {
            ShowLocationOnMapView(mapAPI: $mapAPI)
        }
    }
}

struct PostView_Previews: PreviewProvider {
    static var previews: some View {
        PostView(post: CoreDataPost())
    }
}
