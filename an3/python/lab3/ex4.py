def build_xml_element(tag, content, **elements):
    elementsStr = ' '.join(
        [f'{element}="{elements[element]}"' for element in elements])
    return f'<{tag} {elementsStr}>{content}</{tag}>'



print(build_xml_element("a", "Hello there", href="http://python.org",
                        _class="my-link", id="someid"))
