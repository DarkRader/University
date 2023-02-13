//
//  Post.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 13.02.2023.
//

import Foundation

struct Post: Codable {
    let id: String
    let likes: Int
    let photo: String
    let descrip: String
    let comments: Int
    let city: String
    let country: String
//    let author: Author
}

//struct Author: Codable {
//    let id: String
//    let username: String
//    let avatar: String
//}
