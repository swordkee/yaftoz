/**
 * Yaf Config Ini
 */
/**
 * @namespace
 */
namespace Yaf\Config;

class Ini extends Simple
{
    /**
     * Loads the section $section from the config file $filename for
     * access facilitated by nested object properties.
     *
     * If the section name contains a ":" then the section name to the right
     * is loaded and included into the properties. Note that the keys in
     * this $section will override any keys of the same
     * name in the sections that have been included via ":".
     *
     * If the $section is null, then all sections in the ini file are loaded.
     *
     * If any key includes a ".", then this will act as a separator to
     * create a sub-property.
     *
     * example ini file:
     *      [all]
     *      db.connection = database
     *      hostname = live
     *
     *      [staging : all]
     *      hostname = staging
     *
     * after calling $data = new Yaf_Config_Ini($file, 'staging'); then
     *      $data->hostname === "staging"
     *      $data->db->connection === "database"
     *
     * @param  string        $filename
     * @param  mixed         $section
     * @param  boolean $readonly
     * @throws Yaf_Config_Exception
     * @return void
     */
    public function __construct(string filename, section = null)
    {
        var iniArray, dataArray, sectionName, sectionData;

        let dataArray =  [];
        let iniArray =  [];
        let sectionData =  [];

        if empty(filename) {
            \Yaf\Exception::trigger_error("Unable to find config file " . filename, E_USER_ERROR);
        }

        if is_array(filename) {
            let this->_config = filename;
        } elseif is_string(filename) {
            let iniArray =  this->_loadIniFile(filename);

            if section === null {
                // Load entire file
                for sectionName, sectionData in iniArray {
                    if !is_array(sectionData) {
                        let dataArray = this->_arrayMergeRecursive(dataArray, this->_processKey([], sectionName, sectionData));
                    } else {
                        let dataArray[sectionName] = this->_processSection(iniArray, sectionName);
                    }
                }
                parent::__construct(dataArray, true);
            } else {
                // Load one or more sections

                if !is_array(section) {

                    let section =  [section];
                }

                for sectionName in section {

                    if !isset iniArray[sectionName] {
                        throw new Exception("There is no section '{sectionName}' in '{filename}'");
                    }
                    let dataArray =  this->_arrayMergeRecursive(this->_processSection(iniArray, sectionName), dataArray);
                }
                parent::__construct(dataArray, true);
            }
        } else {
            throw new \Yaf\Exception\TypeError("Invalid parameters provided, must be path of ini file");
        }
    }

    /**
     * Retrieve a value and return null if there is no element set.
     *
     * @param string $name
     * @param mixed $default
     * @return mixed
     */
    public function get(string name)
    {
       var result, names, tmpName;

        //return this if null or empty string, same as yaf

        if !strlen(name) {

            return this;
        }
        let result =  null;
        //check if name contains '.'
        if strpos(name, ".") !== false {
            let result =  this->_config;
            let names =  explode(".", name);
            for tmpName in names {
                //use isset, not array_key_exists, because result may be Yaf_Config_Simple

                if isset result[tmpName] {
                    let result = result[tmpName];
                } else {
                    let result =  null;
                    break;
                }
            }
        } else {

            if array_key_exists(name, this->_config) {
                let result = this->_config[name];
            }
        }

        if is_array(result) {
            let result =  new self(result, this->readonly());
        }

        return result;
    }

    /**
     * Load the INI file from disk using parse_ini_file().
     * @param string $filename
     * @return array
     */
    protected function _parseIniFile(string filename) -> array
    {
        var iniArray;

        //set_error_handler(array($this, '_loadFileErrorHandler'));
        let iniArray =  parse_ini_file(filename, true);
        return iniArray;
    }

    /**
     * Load the ini file and preprocess the section separator (':' in the
     * section name (that is used for section extension) so that the resultant
     * array has the correct section names and the extension information is
     * stored in a sub-key called ';extends'. We use ';extends' as this can
     * never be a valid key name in an INI file that has been loaded using
     * parse_ini_file().
     *
     * @param string $filename
     * @throws Yaf_Config_Exception
     * @return array
     */
    protected function _loadIniFile(string filename) -> array
    {
        var loaded, iniArray, key, data, pieces, thisSection, extendedSection;

        let loaded =  this->_parseIniFile(filename);

        let iniArray =  [];
        for key, data in loaded {
            let pieces =  explode(":", key);
            let thisSection =  trim(pieces[0]);
            switch count(pieces) {
                case 1:
                    let iniArray[thisSection] = data;
                    break;
                case 2:
                    let extendedSection =  trim(pieces[1]);
                    let iniArray[thisSection] = array_merge([";extends" : extendedSection], data);
                    break;
                default:
                    throw new Exception("Section '{thisSection}' may not extend " . "multiple sections in {filename}");
            }
        }
        return iniArray;
    }

    /**
     * Process each element in the section and handle the ";extends" inheritance
     * key. Passes control to _processKey() to handle the nest separator
     * sub-property syntax that may be used within the key name.
     *
     * @param  array  $iniArray
     * @param  string $section
     * @param  array  $config
     * @throws Yaf_Config_Exception
     * @return array
     */
    protected function _processSection(array iniArray, string section, array config = []) -> array
    {
        var thisSection, key, value;

        let thisSection = iniArray[section];

        if is_array(thisSection) {
            for key, value in thisSection {

                if strtolower(key) == ";extends" {

                    if isset iniArray[value] {
                        let config =  this->_processSection(iniArray, value, config);
                    } else {
                        throw new Exception("Parent section '{value}' cannot be found");
                    }
                } else {
                    let config =  this->_processKey(config, key, value);
                }
            }
        }

        return config;
    }

    /**
     * Assign the key's value to the property list. Handles the
     * nest separator for sub-properties.
     *
     * @param  array  $config
     * @param  string $key
     * @param  string $value
     * @throws Yaf_Config_Exception
     * @return array
     */
    protected function _processKey(array config, string key, string value) -> array
    {
        var pieces;
        if strpos(key, ".") !== false {
            let pieces =  explode(".", key, 2);

            if strlen(pieces[0]) && strlen(pieces[1]) {

                if !isset config[pieces[0]] {

                    if pieces[0] === "0" && !empty(config) {
                        // convert the current values in $config into an array
                        let config =  [pieces[0] : config];
                    } else {
                        let config[pieces[0]] = [];
                    }
                } else {

                if !is_array(config[pieces[0]]) {
                    throw new Exception("Cannot create sub-key for '{pieces[0]}' " . "as key already exists");
                }
                }
                let config[pieces[0]] = this->_processKey(config[pieces[0]], pieces[1], value);
            } else {
                throw new Exception("Invalid key '{key}'");
            }
        } else {
            let config[key] = value;
        }
        
        return config;
    }

}