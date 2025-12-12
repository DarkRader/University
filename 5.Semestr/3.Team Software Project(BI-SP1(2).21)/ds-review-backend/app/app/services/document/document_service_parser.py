"""
This module defines class DocumentServiceParser that parsing different types of documents
"""
import json

from models import DocumentType
from bs4 import BeautifulSoup


class DocumentServiceParser:
    """
    Class DocumentServiceParser that parsing different types of documents
    """

    @staticmethod
    def get_type(payload: str) -> DocumentType:
        """
        Detects the file type (HTML, plain text or JSON) based on the input string.
        """
        # Try to parse the string as JSON
        try:
            json.loads(payload)
            return DocumentType.JSON
        except ValueError:
            pass

        # Check if the string contains HTML tags
        try:
            if bool(BeautifulSoup(payload, "html.parser").find()) is True:
                return DocumentType.HTML
        except ValueError:
            pass

        # If none of the above, assume it's plain text
        return DocumentType.PLAIN_TEXT

    def parse(self, payload: str, doc_type: DocumentType) -> str:
        """
        Parsing the document depending on its type
        :param payload: the text, which to be parsed
        :param doc_type: type of the document
        :return: title and content of parsing text
        """
        if doc_type == DocumentType.HTML:
            return self.__parse_html(payload)

        if doc_type == DocumentType.PLAIN_TEXT:
            return self.__parse_plain_text(payload)

        return self.__parse_json(payload)

    @staticmethod
    def __parse_html(raw_document_html: str) -> str:
        """
        :param raw_document_html: The string to be parsed in html format.
        :return parsed title: Title of document in html format.
        """

        soup = BeautifulSoup(raw_document_html, "html.parser")
        title_tag = soup.find("h1")
        title = getattr(title_tag, "string", None)

        return str(title)

    @staticmethod
    def __parse_json(raw_document_json: str) -> str:
        """
        :param raw_document_json: The string to be parsed in json format.
        :return parsed title: Title of document in json format.
        """

        data = json.loads(raw_document_json)
        title = "Default title"
        if "dmp" in data and "title" in data["dmp"]:
            title = data["dmp"]["title"]
        elif "questionnaireName" in data:
            title = data["questionnaireName"]

        return title

    @staticmethod
    def __parse_plain_text(raw_document_plain_text: str) -> str:
        """
        :param raw_document_plain_text: The string to be parsed
        in plain text format.
        :return parsed title: Title of document in pain text format.
        """

        words = raw_document_plain_text.split()
        title = " ".join(words[:2])

        return title
