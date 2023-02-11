//
//  ContentViewMap.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import SwiftUI
import MapKit

struct ContentViewMap: View {
    @StateObject private var mapAPI = MapAPI()
    @State private var text = ""

    var body: some View {
        VStack {
             TextField("Enter an address", text: $text)
                .textFieldStyle(.roundedBorder)
                .padding(.horizontal)

             Button("Find address") {
                mapAPI.getLocation(address: text, delta: 0.5)
             }

             Map(coordinateRegion: $mapAPI.region, annotationItems: mapAPI.locations) { location in
                MapMarker(coordinate: location.coordinate, tint: .blue)
             }
             .ignoresSafeArea()
          }
        .toolbar(.hidden, for: .tabBar)
    }
}

struct ContentViewMap_Previews: PreviewProvider {
    static var previews: some View {
        ContentViewMap()
    }
}
