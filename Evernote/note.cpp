#include "note.h"

using namespace std;

Note::Note()
{}

Note::Note(string guid)
{
    note = evernote.dlNote(guid);
}

Note::Note(en::Note n) : note(n)
{}

string Note::getTitle() const
{
    return note.title;
}

string Note::getContent() const
{
    string c = note.content;
    boost::replace_first(c, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">\n<en-note><div>", "");
    boost::replace_first(c, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\"><en-note><div>", "");
    boost::replace_last(c, "<br clear=\"none\"/></div></en-note>", "");

    return c;
}

string Note::getGuid() const
{
    return note.guid;
}

Notebook Note::getNotebook()
{
    return Notebook(evernote.dlNotebook(note.notebookGuid).name);
}

void Note::setTitle(string title)
{
    if (title.length() > (u_int32_t)evernote::limits::g_Limits_constants.EDAM_NOTE_TITLE_LEN_MAX){
        note.title = title.substr(0, evernote::limits::g_Limits_constants.EDAM_NOTE_TITLE_LEN_MAX);
    }else{
        note.title = title;
    }

    note.__isset.title = true;
}

void Note::setContent(string content)
{
    string header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\"><en-note><div>" ;
    string footer = "<br clear=\"none\"/></div></en-note>";

    if (content.length() > ((u_int32_t)evernote::limits::g_Limits_constants.EDAM_NOTE_TITLE_LEN_MAX - header.length() - footer.length())){
        note.content = header + content.substr(0, evernote::limits::g_Limits_constants.EDAM_NOTE_TITLE_LEN_MAX - header.length() - footer.length()) + footer;
    }else{
        note.content = header + content;
    }

    note.__isset.content = true;
}

void Note::setNotebook(Notebook notebook)
{
    note.notebookGuid = notebook.getGuid();
    note.__isset.notebookGuid = true;
}

void Note::addTag(Tag tag)
{
    note.tagGuids.push_back(tag.getGuid());
    note.__isset.tagGuids = true;
}

void Note::removeTag(Tag tag)
{
    for (vector<en::Guid>::iterator it = note.tagGuids.begin(); it != note.tagGuids.end(); ++it){
        if ( *it == tag.getGuid() ){
            note.tagGuids.erase(it);
        }
    }

    if (note.tagGuids.size() == 0){
        note.__isset.tagGuids = false;
    }
}

void Note::create()
{
    evernote.createNote(note);
}

void Note::downloadMedias()
{
    for (vector<en::Resource>::iterator it = note.resources.begin(); it != note.resources.end(); ++it){
        Resource res((en::Resource)*it);
        res.download();
        cout << res.getFilename() << " downloaded." << endl;
    }
}

ostream& operator << (ostream& os, const Note& note)
{
    os << ConsoleUtils::boldOn << ConsoleUtils::setColorRed << "Titre : " << ConsoleUtils::resetColor << ConsoleUtils::boldOff;
    os << note.getTitle() << endl;
    os << ConsoleUtils::boldOn << ConsoleUtils::setColorYellow << "Contenu : " << ConsoleUtils::resetColor << ConsoleUtils::boldOff;
    os << note.getContent();
    if (note.note.resources.size() > 0){
        os << endl << ConsoleUtils::boldOn << ConsoleUtils::setColorGreen << "Resources : " << ConsoleUtils::resetColor << ConsoleUtils::boldOff;
        os << "Il y a " << note.note.resources.size() << " médias sur cette note";
    }

    return os;
}
