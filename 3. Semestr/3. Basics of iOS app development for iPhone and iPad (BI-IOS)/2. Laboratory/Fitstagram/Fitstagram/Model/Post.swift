//
//  Post.swift
//  Fitstagram
//
//  Created by Артем on 12.10.2022.
//

import Foundation

//{
//    "postedAt" : "2022-04-15T08:46:01Z",
//    "text" : "đ¤",
//    "id" : "E7574AAB-2E6F-43EE-A803-1234953DC36A",
//    "photos" : [
//        "https:\/\/fitstagram.ackee.cz:443\/images\/176C9C71-9FB9-47C8-BE0C-27C9700E3A5C.jpg"
//    ],
//    "likes" : [
//
//    ],
//    "numberOfComments" : 0,
//    "author" : {
//        "username" : "zatim_bez_nazvu",
//        "id" : "C455A70A-A20F-4CAB-8940-F260AFB2F4C6"
//    }
//}

struct Author: Codable, Hashable {
    let username: String
}

struct Post: Identifiable, Hashable, Codable {
    enum CodingKeys: String, CodingKey {
        case id
        case author
        case likes
        case photos
        case description = "text"
        case comments = "numberOfComments
    }
    
    let id: String
    let author: Author
    let photos: [URL]
    let likes: Int
    let description: String
    let comments: Int
    
}

extension Post {
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        
        self.id = try container.decode(String.self, forKey: .id)
        self.author = try container.decode(Author.self, forKey: .author)
        let likes = try container.decode([String], forKey: .likes)
        self.likes = try container.decode(Int.self, forKey: .likes)
        self.description = try container.decode(String.self, forKey: .description)
        self.comments = try container.decode(Int.self, forKey: .comments)
        self.photos = try container.decode([URL], forKey: .photos)
    }
}
