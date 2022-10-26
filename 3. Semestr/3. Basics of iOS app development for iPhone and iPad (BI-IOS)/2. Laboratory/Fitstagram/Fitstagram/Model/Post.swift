//
//  Post.swift
//  Fitstagram
//
//  Created by Артем on 12.10.2022.
//

import Foundation

struct Post: Identifiable, Hashable {
    let id: String = UUID().uuidString
    let username: String
    let likes: Int
    let description: String
    let comments: Int
}
