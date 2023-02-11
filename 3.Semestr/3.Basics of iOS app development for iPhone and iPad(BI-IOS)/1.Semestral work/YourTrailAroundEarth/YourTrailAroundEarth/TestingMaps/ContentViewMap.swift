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
    
    private var startLocation: String
    
    private var startDelta: Double
    
    private var suitableDelta: Double
    
    init(startLocation: String, startDelta: Double, suitableDelta: Double) {
        self.startLocation = startLocation
        self.startDelta = startDelta
        self.suitableDelta = suitableDelta
    }

    var body: some View {
        VStack {
             TextField("Enter an address", text: $text)
                .textFieldStyle(.roundedBorder)
                .padding(.horizontal)

            if text != "" {
                Button("Find address") {
                    mapAPI.getLocation(address: text, delta: suitableDelta)
                }
            } else {
                Button("Show current location") {
                    mapAPI.getLocation(address: startLocation, delta: startDelta)
                }
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
        ContentViewMap(startLocation: "USA", startDelta: 20, suitableDelta: 5)
    }
}
