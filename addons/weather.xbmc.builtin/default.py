import sys, urllib, urllib2, xbmc, xbmcgui, xbmcaddon
import xml.etree.ElementTree as ET
from urlparse import urlparse, parse_qs


class WeatherError(Exception):
    pass


class Location:
    def __init__(self, id, name, region, country, lat, lon):
        self.id = id
        self.name = name
        self.region = region
        self.country = country
        self.lat = lat
        self.lon = lon


class WeatherAPI:
    api = "https://services.gismeteo.net/inform-service/inf_chrome/cities"

    @staticmethod
    def _extract_xml(r):

        try:
            return ET.fromstring(r)
        except (ValueError, ET.ParseError) as e:
            xbmc.log("Weather API: error when parsing response\n Error {1}".format(str(e)))

        return None

    def make_request(self, url):
        try:
            request = urllib2.Request(url)
            request.add_header("User-Agent", "XBMC4Xbox/4.0")
            response = urllib2.urlopen(request)
            return response.read()
        except Exception as e:
            xbmc.log("Weather API: error when calling: {0}\n Error {1}".format(url, str(e)))

        xbmcgui.Dialog().notification("Weather API", xbmc.getLocalizedString(15301), xbmcgui.NOTIFICATION_ERROR)
        return None

    def search_location(self, query):
        url = "{0}?{1}".format(
            self.api,
            urllib.urlencode({"lang": "en", "startsWith": query}),
        )

        body = self.make_request(url)
        if not body:
            return []

        root = self._extract_xml(body)
        if root is None:
            return []

        items = []
        for item in root.findall("item"):
            items.append({"id": item.attrib["id"],
                              "name": item.attrib["n"],
                              "region": item.attrib["district_name"],
                              "country": item.attrib["country_name"],
                              "lat": item.attrib["lat"],
                              "lon": item.attrib["lng"]})

        return items


def run(id, addon):
    kbd = xbmc.Keyboard("", xbmc.getLocalizedString(14024), False)
    kbd.doModal()
    if not kbd.isConfirmed():
        return
    query = kbd.getText()

    service = WeatherAPI()
    search_result = service.search_location(query)
    if search_result is None:
        return

    locations = []
    labels = []
    for item in search_result:
        location = Location(
            item["id"],
            item["name"],
            item["region"],
            item["country"],
            item["lat"],
            item["lon"],
        )
        locations.append(location)
        labels.append("{0}, {1}".format(item["name"], item["country"]))

    if locations:
        selected = xbmcgui.Dialog().select(xbmc.getLocalizedString(396), labels)
        if selected != -1:
            selected_location = locations[selected]
            addon.setSetting("Location{}".format(id), selected_location.name)
            addon.setSetting("Location{}ID".format(id), str(selected_location.id))
            addon.setSetting(
                "Location{}LAT".format(id), str(selected_location.lat)
            )
            addon.setSetting(
                "Location{}LON".format(id), str(selected_location.lon)
            )
    else:
        xbmcgui.Dialog().ok(
            "Weather API (Internal Weather)", xbmc.getLocalizedString(284), "", ""
        )
        run(id, addon)


if __name__ == "__main__":
    addon = xbmcaddon.Addon()

    parsed_query = urlparse("?" + sys.argv[1])
    params = parse_qs(parsed_query.query)
    id_param = params.get("id", [None])[0]

    run(id_param, addon)
