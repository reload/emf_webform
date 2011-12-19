-- SUMMARY --

Module to integrate the E-mail Marketing Framework (EMF) and Webform modules.

EMF webform provides a new Webform component which allows the creator to select a set of mailing lists exposed through EMF and link them to an email field. If the user selects one or more of the lists when submitting the form she also subscribes to the lists through EMF.

For a full description of the module, visit the project page:
  http://drupal.org/project/emf_webform

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/emf_webform


-- REQUIREMENTS --

The module requires the E-mail Marketing Framework (http://drupal.org/project/emf) and Webform (http://drupal.org/project/webform) modules (version 3.x) to be enabled.


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

* Make sure the E-mail Marketing Framework is configured with a mailing list service and there are activated lists available. This can be verified at /admin/build/emf.
* Create or edit a webform node
* Go to the Webform -> Form components for the webform
* Create a new component. As type select "E-mail marketing framework list signup"
* Add form component configuration
  * Select lists which should be available for subscription in the webform.
  * Select the field which contains the user email address to subscribe. The field must be of type email.

When the webform is rendered each of the selected lists will be displayed with a checkbox. The label for each checkbox is the action name for the corresponding list.


-- CONTACT --

Current maintainers:
* Kasper Garnæs (kasperg) - http://drupal.org/user/331389

This project is been developed by Reload! and sponsored by FDB.
