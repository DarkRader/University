//
//  CountryListView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 04.02.2023.
//

import SwiftUI

struct CountryListView: View {
    var body: some View {
      List(NSLocale.isoCountryCodes, id: \.self) { countryCode in
        HStack {
          Text(countryFlag(countryCode))
          Text(Locale.current.localizedString(forRegionCode: countryCode) ?? "")
          Spacer()
          Text(countryCode)
        }
      }
    }
      func countryFlag(_ countryCode: String) -> String {
        String(String.UnicodeScalarView(countryCode.unicodeScalars.compactMap {
          UnicodeScalar(127397 + $0.value)
        }))
      }
}

struct CountryListView_Previews: PreviewProvider {
    static var previews: some View {
        CountryListView()
    }
}
