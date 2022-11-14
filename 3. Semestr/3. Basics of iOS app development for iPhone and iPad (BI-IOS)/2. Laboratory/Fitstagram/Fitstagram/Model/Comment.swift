//
//  Comment.swift
//  Fitstagram
//
//  Created by Артем on 19.10.2022.
//

import Foundation

struct Comment: Identifiable, Decodable {
    let id: String
    let author: User
    let text: String
}
