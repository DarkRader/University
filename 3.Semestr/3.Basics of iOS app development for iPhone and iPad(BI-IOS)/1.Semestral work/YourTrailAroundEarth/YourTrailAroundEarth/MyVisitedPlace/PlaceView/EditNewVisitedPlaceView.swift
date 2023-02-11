//
//  EditNewVisitedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 11.02.2023.
//

import SwiftUI

struct EditNewVisitedPlaceView: View {
    
    private var place: CoreDataPlace
    
    init(place: CoreDataPlace) {
        self.place = place
    }
    
    var body: some View {
        Text(/*@START_MENU_TOKEN@*/"Hello, World!"/*@END_MENU_TOKEN@*/)
    }
}

struct EditNewVisitedPlaceView_Previews: PreviewProvider {
    static var previews: some View {
        EditNewVisitedPlaceView(place: CoreDataPlace())
    }
}
